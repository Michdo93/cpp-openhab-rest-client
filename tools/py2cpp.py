"""
Generates the REST classes of cpp-openhab-rest-client from python-openhab-rest-client.

The Python library is the reference: every method of a REST class is translated
statement by statement (same endpoint, headers, query parameters, body, status
handling and messages). Python values become py::V (an nlohmann::json value) handled
by the runtime in src/py_rt.cpp; try/except becomes try/catch. Only a small, regular
subset of Python is supported; anything else raises an error so that nothing is
translated silently wrong.

Naming: Python class Items -> openhab::Items, method getItems -> Items::getItems.
Required parameters come first, optional ones keep the Python order and defaults
(None -> std::optional / json null). For every method with optional parameters there
is also an overload taking an argument struct:

    json r = items.getItems(std::nullopt, std::nullopt, "Light");      // positional
    openhab::Items::GetItemsArgs a;  a.tags = "Light";  items.getItems(a);
    items.getItems({.tags = "Light", .fields = "name,state"});         // C++20

Usage: python3 py2cpp.py <path to python-openhab-rest-client/openhab> <repository root>
       python3 py2cpp.py --readme <path>     (method tables for README.md)
       python3 py2cpp.py --dispatch <path>   (test/dispatch.cpp for the differential test)
"""
import ast
import glob
import json
import os
import sys

SKIP_FILES = ("Async", "__", "Client", "SSE")
CPP_KEYWORDS = {"auto", "break", "case", "char", "const", "continue", "default", "do",
                "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline",
                "int", "long", "register", "return", "short", "signed", "sizeof", "static",
                "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
                "while", "namespace", "class", "new", "delete", "this", "template",
                "operator", "private", "public", "protected", "virtual", "friend", "using",
                "typename", "bool", "true", "false", "export", "try", "catch", "throw",
                "explicit", "mutable", "and", "or", "not", "xor", "compl", "bitand", "bitor",
                "default", "errno", "module", "import", "requires", "concept"}

NAME_TYPES = {"language": "str", "prefix": "str", "typeFilter": "str", "moduleTypeUID": "str",
              "channelTypeUID": "str", "itemType": "str", "tags": "str",
              "summary": "bool", "staticDataOnly": "bool"}


def cname(n):
    """C++ name of a parameter (keywords get a trailing underscore)."""
    return n + "_" if n in CPP_KEYWORDS else n


class Unsupported(Exception):
    pass


def cstr(s):
    return json.dumps(s, ensure_ascii=False)


def ptype(arg, default):
    """Python type of a parameter: str, bool, int, float, json."""
    if arg.annotation is not None:
        a = ast.unparse(arg.annotation)
        t = {"str": "str", "bool": "bool", "int": "int", "float": "float",
             "dict": "json", "list": "json"}.get(a)
        if not t:
            raise Unsupported(f"annotation {a}")
        return t
    if arg.arg in NAME_TYPES:
        return NAME_TYPES[arg.arg]
    if isinstance(default, ast.Constant):
        v = default.value
        if isinstance(v, bool):
            return "bool"
        if isinstance(v, str):
            return "str"
        if isinstance(v, int):
            return "int"
        if isinstance(v, float):
            return "float"
    return "json"


class Method:
    def __init__(self, cls, fn):
        self.cls, self.fn, self.name = cls, fn, fn.name
        a = fn.args
        args = a.args[1:]
        defaults = [None] * (len(args) - len(a.defaults)) + list(a.defaults)
        self.params = []   # (name, type, default node or None, required)
        for arg, d in zip(args, defaults):
            self.params.append((arg.arg, ptype(arg, d), d, d is None))
        self.private = fn.name.startswith("_")
        self.stream = False

    @property
    def impl(self):
        return f"{self.cls}_{self.name.lstrip('_')}"

    @property
    def required(self):
        return [p for p in self.params if p[3]]

    @property
    def optional(self):
        return [p for p in self.params if not p[3]]

    @property
    def args_struct(self):
        return self.name[0].upper() + self.name[1:] + "Args"


def always_returns(stmts):
    for s in stmts:
        if isinstance(s, (ast.Return, ast.Raise)):
            return True
        if isinstance(s, ast.If) and s.orelse and always_returns(s.body) and always_returns(s.orelse):
            return True
        if isinstance(s, ast.Try) and always_returns(s.body) and \
                all(always_returns(h.body) for h in s.handlers):
            return True
    return False


class Translator:
    def __init__(self, method, methods):
        self.m, self.methods = method, methods
        self.where = f"{method.cls}.{method.name}"
        self.params = {p[0] for p in method.params}
        self.errname = None     # name of the exception variable in an except block

    def fail(self, what):
        raise Unsupported(f"{self.where}: {what}")

    # expressions: (C++ code, kind) – "obj" = py::V, "bool" = bool, "stream" = EventStream
    def cond(self, n):
        code, kind = self.expr(n)
        return code if kind == "bool" else f"py::truthy({code})"

    def obj(self, n):
        code, kind = self.expr(n)
        if kind == "bool":
            return f"py::V(json({code}))"
        if kind == "stream":
            self.fail("stream used as value")
        return code

    def expr(self, n):
        m = getattr(self, "e_" + type(n).__name__, None)
        if not m:
            self.fail(f"expression {ast.unparse(n)}")
        return m(n)

    def e_Constant(self, n):
        v = n.value
        if v is None:
            return "py::V()", "obj"
        if v is True or v is False:
            return f"py::V(json({'true' if v else 'false'}))", "obj"
        if isinstance(v, str):
            return f"py::s({cstr(v)})", "obj"
        if isinstance(v, int):
            return f"py::V(json({v}))", "obj"
        if isinstance(v, float):
            return f"py::V(json({v!r}))", "obj"
        self.fail(f"constant {v!r}")

    def e_Name(self, n):
        if n.id == self.errname:
            self.fail("exception object used as value")
        return f"v_{n.id}", "obj"

    def e_JoinedStr(self, n):
        parts = []
        for v in n.values:
            if isinstance(v, ast.Constant):
                parts.append(f"py::s({cstr(v.value)})")
            elif isinstance(v, ast.FormattedValue):
                if v.format_spec is not None or v.conversion != -1:
                    self.fail("format spec")
                parts.append(self.strarg(v.value))
        return f"py::cat({{{', '.join(parts)}}})", "obj"

    def strarg(self, n):
        """str(x) inside an f-string – handles str(err)."""
        if isinstance(n, ast.Name) and n.id == self.errname:
            return "py::excStr(e_err)"
        if isinstance(n, ast.Call) and isinstance(n.func, ast.Name) and n.func.id == "str" \
                and isinstance(n.args[0], ast.Name) and n.args[0].id == self.errname:
            return "py::excStr(e_err)"
        return self.obj(n)

    def e_Dict(self, n):
        if not n.keys:
            return "py::dict()", "obj"
        parts = []
        for k, v in zip(n.keys, n.values):
            if not (isinstance(k, ast.Constant) and isinstance(k.value, (str, int))):
                self.fail(f"dict key {ast.unparse(k) if k else '**'}")
            parts.append(f"{{{cstr(str(k.value))}, {self.obj(v)}}}")
        return f"py::dict({{{', '.join(parts)}}})", "obj"

    def e_List(self, n):
        if not n.elts:
            return "py::list()", "obj"
        items = [self.obj(e) for e in n.elts]
        return f"py::list({{{', '.join(items)}}})", "obj"

    e_Tuple = e_List

    def e_Subscript(self, n):
        if isinstance(n.slice, ast.Slice):
            self.fail("slice")
        return f"py::get({self.obj(n.value)}, {self.obj(n.slice)})", "obj"

    def e_Attribute(self, n):
        src = ast.unparse(n)
        if self.errname and src == f"{self.errname}.response.status_code":
            return "py::excStatus(e_err)", "obj"
        self.fail(f"attribute {src}")

    def e_BoolOp(self, n):
        # short-circuit like Python: the right side is only evaluated if needed
        vals = [self.obj(v) for v in n.values]
        out = vals[-1]
        for v in reversed(vals[:-1]):
            if isinstance(n.op, ast.And):
                out = f"[&]() -> py::V {{ py::V t_ = {v}; return py::truthy(t_) ? {out} : t_; }}()"
            else:
                out = f"[&]() -> py::V {{ py::V t_ = {v}; return py::truthy(t_) ? t_ : {out}; }}()"
        return out, "obj"

    def e_UnaryOp(self, n):
        if isinstance(n.op, ast.Not):
            return f"!{self.cond(n.operand)}", "bool"
        if isinstance(n.op, ast.USub) and isinstance(n.operand, ast.Constant):
            return f"py::V(json(-{n.operand.value!r}))", "obj"
        self.fail(ast.unparse(n))

    def e_IfExp(self, n):
        return f"({self.cond(n.test)} ? py::V({self.obj(n.body)}) : py::V({self.obj(n.orelse)}))", "obj"

    def e_Compare(self, n):
        if len(n.ops) != 1:
            self.fail(ast.unparse(n))
        op, L, R = n.ops[0], n.left, n.comparators[0]
        none_r = isinstance(R, ast.Constant) and R.value is None
        if isinstance(op, (ast.Is, ast.IsNot)):
            if not none_r:
                self.fail("'is' with something else than None")
            code = f"py::isnone({self.obj(L)})"
            return (code if isinstance(op, ast.Is) else f"!{code}"), "bool"
        lc, rc = self.obj(L), self.obj(R)
        if isinstance(op, ast.Eq):
            return f"py::eq({lc}, {rc})", "bool"
        if isinstance(op, ast.NotEq):
            return f"!py::eq({lc}, {rc})", "bool"
        if isinstance(op, ast.In):
            return f"py::contains({rc}, {lc})", "bool"
        if isinstance(op, ast.NotIn):
            return f"!py::contains({rc}, {lc})", "bool"
        sym = {ast.Lt: "<", ast.Gt: ">", ast.LtE: "<=", ast.GtE: ">="}[type(op)]
        return f"(py::cmp({lc}, {rc}) {sym} 0)", "bool"

    def e_DictComp(self, n):
        gen = n.generators[0]
        if (len(n.generators) == 1 and ast.unparse(gen.iter).endswith(".items()")
                and len(gen.ifs) == 1 and ast.unparse(n.key) == ast.unparse(gen.target.elts[0])
                and ast.unparse(n.value) == ast.unparse(gen.target.elts[1])
                and ast.unparse(gen.ifs[0]) == f"{gen.target.elts[1].id} is not None"):
            return f"py::withoutNone({self.obj(gen.iter.func.value)})", "obj"
        self.fail(f"dict comprehension {ast.unparse(n)}")

    @staticmethod
    def kwargs(n):
        return {k.arg: k.value for k in n.keywords}

    def call_args(self, names, n):
        vals = [None] * len(names)
        for i, a in enumerate(n.args):
            vals[i] = a
        for k in n.keywords:
            if k.arg not in names:
                self.fail(f"keyword {k.arg}")
            vals[names.index(k.arg)] = k.value
        return vals

    def default_value(self, node):
        if node is None:
            return "py::V()"
        return self.obj(node)

    def e_Call(self, n):
        f = n.func
        src = ast.unparse(f)
        kw = self.kwargs(n)
        if src.startswith("self.client.") or src == "client.executeSSE":
            verb = f.attr
            path = n.args[0] if n.args else kw.pop("endpoint", None) or kw.pop("url")
            h = self.obj(kw["headers"]) if "headers" in kw else "py::V()"
            prm = self.obj(kw["params"]) if "params" in kw else "py::V()"
            data = self.obj(kw["data"]) if "data" in kw else "py::V()"
            if verb in ("get", "post", "put", "delete"):
                return f'py::http(C, "{verb}", {self.obj(path)}, {h}, {data}, {prm})', "obj"
            if verb == "executeSSE":
                return f"py::sse(C, {self.obj(path)}, {h}, {prm})", "stream"
            self.fail(f"client.{verb}")
        if isinstance(f, ast.Attribute) and isinstance(f.value, ast.Name) and f.value.id == "self":
            target = self.methods.get(f.attr)
            if target is None:
                self.fail(f"unknown method self.{f.attr}")
            vals = self.call_args([p[0] for p in target.params], n)
            args = ["C"]
            for (pname, t, d, req), v in zip(target.params, vals):
                if v is None:
                    if req:
                        self.fail(f"missing argument {pname}")
                    args.append(self.default_value(d))
                else:
                    args.append(self.obj(v))
            return f"{target.impl}({', '.join(args)})", "stream" if target.stream else "obj"
        if isinstance(f, ast.Name):
            name = f.id
            if name == "str":
                a0 = n.args[0]
                if isinstance(a0, ast.Name) and a0.id == self.errname:
                    return "py::excStr(e_err)", "obj"
                return f"py::str({self.obj(a0)})", "obj"
            if name == "isinstance":
                t = ast.unparse(n.args[1])
                fn = {"StatusResponse": "py::isstatus", "dict": "py::isdict", "list": "py::islist",
                      "(list, tuple)": "py::islist", "str": "py::isstr", "bool": "py::isbool"}.get(t)
                if not fn:
                    self.fail(f"isinstance {t}")
                return f"{fn}({self.obj(n.args[0])})", "bool"
            if name == "quote":
                safe = kw.get("safe")
                s = safe.value if isinstance(safe, ast.Constant) else "/"
                return f"py::quote({self.obj(n.args[0])}, {cstr(s)})", "obj"
            if name == "urlencode":
                return f"py::urlencode({self.obj(n.args[0])})", "obj"
            if name == "dict":
                return f"py::copy({self.obj(n.args[0])})", "obj"
            if name == "len":
                return f"py::len({self.obj(n.args[0])})", "obj"
            if name == "_openStream":
                names = ["client", "topics", "path", "headers", "errors"]
                vals = self.call_args(names, n)
                a = [self.obj(v) if v is not None else "py::V()" for v in vals[1:]]
                return f"py::openStream(C, {', '.join(a)})", "stream"
            self.fail(f"call {name}")
        if isinstance(f, ast.Attribute):
            a = f.attr
            vsrc = ast.unparse(f.value)
            if vsrc == "json" and a == "dumps":
                return f"py::dumps({self.obj(n.args[0])})", "obj"
            if vsrc == "urllib.parse" and a == "quote":
                safe = kw.get("safe")
                s = safe.value if isinstance(safe, ast.Constant) else "/"
                return f"py::quote({self.obj(n.args[0])}, {cstr(s)})", "obj"
            obj = self.obj(f.value)
            args = [self.obj(x) for x in n.args]
            if a == "get":
                return f"py::getOr({obj}, {', '.join(args)})", "obj"
            if a == "lower":
                return f"py::lower({obj})", "obj"
            if a == "strip" and not args:
                return f"py::strip({obj})", "obj"
            if a == "rstrip":
                return f"py::rstrip({obj}, {args[0]})", "obj"
            if a == "split":
                return f"py::split({obj}, {args[0]})", "obj"
            if a == "join":
                return f"py::join({obj}, {args[0]})", "obj"
        self.fail(f"call {ast.unparse(n)}")

    # ------------------------------------------------------------------ statements
    def block(self, stmts, ind):
        out = []
        for s in stmts:
            out += self.stmt(s, ind)
            if always_returns([s]):
                break
        return out

    def ret(self, value, p):
        if value is None:
            return [f"{p}return py::asStream(py::V());"] if self.m.stream else [f"{p}return py::V();"]
        code, kind = self.expr(value)
        if kind == "bool":
            code, kind = f"py::V(json({code}))", "obj"
        if self.m.stream and kind != "stream":
            return [f"{p}return py::asStream({code});"]
        if not self.m.stream and kind == "stream":
            self.fail("stream returned from a normal method")
        return [f"{p}return {code};"]

    def stmt(self, s, ind):
        p = "    " * ind
        if isinstance(s, ast.Expr) and isinstance(s.value, ast.Constant):
            return []
        if isinstance(s, ast.Expr) and isinstance(s.value, ast.Call):
            code, kind = self.expr(s.value)
            return [f"{p}(void){code};"]
        if isinstance(s, ast.Return):
            return self.ret(s.value, p)
        if isinstance(s, ast.Assign):
            if len(s.targets) != 1:
                self.fail("multiple assignment")
            t = s.targets[0]
            if isinstance(t, ast.Name):
                return [f"{p}v_{t.id} = {self.obj(s.value)};"]
            if isinstance(t, ast.Subscript) and isinstance(t.value, ast.Name):
                return [f"{p}py::set(v_{t.value.id}, {self.obj(t.slice)}, {self.obj(s.value)});"]
            self.fail(f"assignment to {ast.unparse(t)}")
        if isinstance(s, ast.If):
            out = [f"{p}if ({self.cond(s.test)}) {{"] + self.block(s.body, ind + 1)
            orelse = s.orelse
            while len(orelse) == 1 and isinstance(orelse[0], ast.If):
                e = orelse[0]
                out += [f"{p}}} else if ({self.cond(e.test)}) {{"] + self.block(e.body, ind + 1)
                orelse = e.orelse
            if orelse:
                out += [f"{p}}} else {{"] + self.block(orelse, ind + 1)
            return out + [p + "}"]
        if isinstance(s, ast.Try):
            if s.orelse or s.finalbody:
                self.fail("try/else/finally")
            out = [f"{p}try {{"] + self.block(s.body, ind + 1)
            for h in s.handlers:
                t = ast.unparse(h.type)
                if t.endswith("HTTPError"):
                    ctype = "py::HTTPError"
                elif t.endswith("RequestException"):
                    ctype = "py::RequestException"
                else:
                    self.fail(f"except {t}")
                old = self.errname
                self.errname = h.name
                body = self.block(h.body, ind + 1)
                self.errname = old
                var = "e_err" if h.name else ""
                out += [f"{p}}} catch (const {ctype}& {var}) {{"]
                if h.name:
                    out.append(f"{p}    (void)e_err;")
                out += body
            return out + [p + "}"]
        if isinstance(s, ast.Pass):
            return []
        self.fail(f"statement {type(s).__name__}: {ast.unparse(s)[:80]}")


def returns_stream(fn, methods):
    for n in ast.walk(fn):
        if isinstance(n, ast.Return) and isinstance(n.value, ast.Call):
            src = ast.unparse(n.value.func)
            if src in ("_openStream", "self.client.executeSSE", "client.executeSSE"):
                return True
            if src.startswith("self.") and src[5:] in methods and methods[src[5:]].stream:
                return True
    return False


def doc_lines(fn):
    doc = ast.get_docstring(fn) or ""
    lines = [l.rstrip().replace("*/", "* /").replace("/*", "/ *") for l in doc.splitlines()]
    while lines and not lines[-1]:
        lines.pop()
    return lines


REQ_TYPES = {"str": "const std::string&", "bool": "bool", "int": "int", "float": "double",
             "json": "const json&"}
OPT_NONE = {"str": "std::optional<std::string>", "bool": "std::optional<bool>",
            "int": "std::optional<int>", "float": "std::optional<double>", "json": "json"}
OPT_VAL = {"str": "std::string", "bool": "bool", "int": "int", "float": "double", "json": "json"}


def default_cpp(t, d, where):
    """C++ default value of an optional parameter."""
    if d is None or (isinstance(d, ast.Constant) and d.value is None):
        return "nullptr" if t == "json" else "std::nullopt"
    if isinstance(d, ast.Constant):
        v = d.value
        if isinstance(v, bool):
            return "true" if v else "false"
        if isinstance(v, str):
            return cstr(v) if t == "str" else f"json({cstr(v)})"
        if isinstance(v, (int, float)):
            return repr(v) if t in ("int", "float") else f"json({v!r})"
    if isinstance(d, ast.Dict) and not d.keys:
        return "json::object()"
    if isinstance(d, ast.List) and not d.elts:
        return "json::array()"
    raise Unsupported(f"{where}: default {ast.unparse(d)}")


def is_none_default(d):
    return d is None or (isinstance(d, ast.Constant) and d.value is None)


def opt_member_type(t, d):
    return OPT_NONE[t] if is_none_default(d) else OPT_VAL[t]


def opt_param_type(t, d):
    tt = opt_member_type(t, d)
    if tt in ("bool", "int", "double"):
        return tt
    return f"const {tt}&"


def signature(m, with_defaults):
    where = f"{m.cls}.{m.name}"
    parts = [f"{REQ_TYPES[t]} {cname(n)}" for n, t, d, r in m.required]
    for n, t, d, r in m.optional:
        s = f"{opt_param_type(t, d)} {cname(n)}"
        if with_defaults:
            s += f" = {default_cpp(t, d, where)}"
        parts.append(s)
    return parts


def method_code(m, methods):
    tr = Translator(m, methods)
    fn = m.fn
    assigned = {t.id for n in ast.walk(fn) if isinstance(n, ast.Assign)
                for t in n.targets if isinstance(t, ast.Name)}
    params = [p[0] for p in m.params]
    locals_ = sorted(assigned - set(params))
    rtype = "EventStream" if m.stream else "py::V"
    sig = ["OpenHABClient& C"] + [f"py::V v_{n}" for n in params]
    out = [f"static {rtype} {m.impl}({', '.join(sig)}) {{", "    (void)C;"]
    for v in params:
        out.append(f"    (void)v_{v};")
    for v in locals_:
        out.append(f"    py::V v_{v};")
    out += tr.block(fn.body, 1)
    if not always_returns(fn.body):
        out.append("    return py::asStream(py::V());" if m.stream else "    return py::V();")
    out.append("}")
    if not m.private:
        out += [""] + public_code(m)
    return out


def public_code(m):
    ret = "EventStream" if m.stream else "json"
    args = ["*client_"] + [f"py::arg({cname(n)})" for n, *_ in m.params]
    call = f"{m.impl}({', '.join(args)})"
    fin = "py::finishStream" if m.stream else "py::finish"
    out = [f"{ret} {m.cls}::{m.name}({', '.join(signature(m, False))}) {{",
           f"    return {fin}([&] {{ return {call}; }});", "}"]
    if m.optional:
        req = [f"{REQ_TYPES[t]} {cname(n)}" for n, t, d, r in m.required]
        sig = req + [f"const {m.args_struct}& a"]
        call_args = [cname(n) for n, *_ in m.required] + [f"a.{cname(n)}" for n, *_ in m.optional]
        out += ["", f"{ret} {m.cls}::{m.name}({', '.join(sig)}) {{",
                f"    return {m.name}({', '.join(call_args)});", "}"]
    return out


def decl(prefix, params, suffix, indent="    "):
    """Declaration wrapped at 100 columns, parameters aligned after the parenthesis."""
    one = f"{indent}{prefix}({', '.join(params)}){suffix}"
    if len(one) <= 100 or not params:
        return [one]
    pad = " " * (len(indent) + len(prefix) + 1)
    lines, cur = [], f"{indent}{prefix}("
    for i, p in enumerate(params):
        piece = p + ("," if i < len(params) - 1 else f"){suffix}")
        if cur.endswith("(") or len(cur) + 1 + len(piece) <= 100:
            cur += ("" if cur.endswith("(") else " ") + piece
        else:
            lines.append(cur)
            cur = pad + piece
    return lines + [cur]


def header_code(m):
    out = []
    ret = "EventStream" if m.stream else "json"
    if m.optional:
        out.append(f"    /** Optional arguments of {m.name}() – the defaults of the Python library. */")
        out.append(f"    struct {m.args_struct} {{")
        for n, t, d, r in m.optional:
            dflt = "" if is_none_default(d) else f" = {default_cpp(t, d, m.cls + '.' + m.name)}"
            out.append(f"        {opt_member_type(t, d)} {cname(n)}{dflt};")
        out.append("    };")
        out.append("")
    out.append("    /**")
    out += ["     * " + l if l else "     *" for l in doc_lines(m.fn)]
    out.append("     */")
    out += decl(f"{ret} {m.name}", signature(m, True), ";")
    if m.optional:
        req = [f"{REQ_TYPES[t]} {cname(n)}" for n, t, d, r in m.required]
        out.append(f"    /** {m.name}() with the optional arguments as struct. */")
        out += decl(f"{ret} {m.name}", req + [f"const {m.args_struct}& a"], ";")
    out.append("")
    return out


def load_classes(src):
    files = sorted(f for f in glob.glob(os.path.join(src, "*.py"))
                   if not os.path.basename(f).startswith(SKIP_FILES))
    result = []
    for f in files:
        tree = ast.parse(open(f, encoding="utf-8").read())
        for c in tree.body:
            if not isinstance(c, ast.ClassDef):
                continue
            fns = [fn for fn in c.body if isinstance(fn, ast.FunctionDef) and fn.name != "__init__"]
            methods = {fn.name: Method(c.name, fn) for fn in fns}
            for _ in range(3):
                for m in methods.values():
                    m.stream = returns_stream(m.fn, methods)
            result.append((os.path.basename(f), c, methods))
    return result


def generate(src, root):
    errors = []
    header = ["// Generated from python-openhab-rest-client by tools/py2cpp.py – do not edit.",
              "#pragma once", "", '#include "OpenHABClient.hpp"', "",
              "#include <optional>", "#include <string>", "", "namespace openhab {", ""]
    files = {}
    for fname, c, methods in load_classes(src):
        try:
            code = []
            for m in methods.values():
                code += method_code(m, methods) + [""]
            hdr = []
            for m in methods.values():
                if not m.private:
                    hdr += header_code(m)
        except Unsupported as e:
            errors.append(str(e))
            continue
        cdoc = (ast.get_docstring(c) or "").strip()
        header += [f"// ── {c.name} " + "─" * max(3, 74 - len(c.name)), ""]
        if cdoc:
            header += ["/** " + " ".join(l.strip() for l in cdoc.splitlines() if l.strip()) + " */"]
        header += [f"class OPENHAB_API {c.name} {{", "public:",
                   f"    explicit {c.name}(OpenHABClient& client) : client_(&client) {{}}", ""]
        header += hdr
        header += ["private:", "    OpenHABClient* client_;", "};", ""]
        fwd = []
        for m in methods.values():
            rtype = "EventStream" if m.stream else "py::V"
            sig = ["OpenHABClient& C"] + [f"py::V v_{p[0]}" for p in m.params]
            fwd.append(f"static {rtype} {m.impl}({', '.join(sig)});")
        files.setdefault(fname, []).append((c.name, fwd, code))
    header += ["}  // namespace openhab", ""]
    if errors:
        for e in errors:
            print("UNSUPPORTED:", e, file=sys.stderr)
        sys.exit(1)
    with open(os.path.join(root, "include", "openhab", "API.hpp"), "w", encoding="utf-8") as f:
        f.write("\n".join(header))
    gen = os.path.join(root, "src", "api")
    os.makedirs(gen, exist_ok=True)
    for old in glob.glob(os.path.join(gen, "*.cpp")):
        os.remove(old)
    names = []
    for fname, classes in files.items():
        base = fname[:-3]
        out = [f"// Generated from {fname} of python-openhab-rest-client by tools/py2cpp.py – "
               "do not edit.", '#include "../py_rt.hpp"', '#include "openhab/API.hpp"', "",
               "namespace openhab {", ""]
        for cname_, fwd, code in classes:
            names.append(cname_)
            out += fwd + [""] + code
        out += ["}  // namespace openhab", ""]
        with open(os.path.join(gen, base + ".cpp"), "w", encoding="utf-8") as f:
            f.write("\n".join(out))
    print(f"{len(names)} classes: {', '.join(names)}", file=sys.stderr)


def readme_tables(src):
    out = []
    for fname, c, methods in sorted(load_classes(src), key=lambda x: x[1].name.lower()):
        out += [f"### {c.name}", "", "| Method | Parameters | Optional (defaults as in Python) | Returns |",
                "|---|---|---|---|"]
        for m in methods.values():
            if m.private:
                continue
            req = ", ".join(cname(p[0]) for p in m.required)
            opt = ", ".join(cname(p[0]) for p in m.optional)
            out.append(f"| `{m.name}` | {req} | {opt} | "
                       f"{'`EventStream`' if m.stream else '`json`'} |")
        out.append("")
    return "\n".join(out)


def dispatch_code(src):
    """test/dispatch.cpp: calls any method by class and method name with JSON arguments
    (positional list, a trailing object for named arguments) – for the differential test.
    Methods with optional parameters are called with their argument struct."""
    conv = {"str": "s_", "bool": "b_", "int": "i_", "float": "d_", "json": "j_"}
    optconv = {"str": "os_", "bool": "ob_", "int": "oi_", "float": "od_", "json": "j_"}
    out = ["// Generated by tools/py2cpp.py --dispatch – test helper.",
           "#include <openhab/openhab.hpp>", "", "using openhab::json;", "",
           "static const json NONE = nullptr;",
           "static const json& arg_(const json& a, size_t i, const json* kw, const char* n) {",
           "    size_t npos = a.size() - (kw ? 1 : 0);",
           "    if (i < npos) return a[i];",
           "    if (kw && kw->contains(n)) return (*kw)[n];",
           "    return NONE;", "}",
           "static std::string s_(const json& v) { return v.is_string() ? v.get<std::string>() : \"\"; }",
           "static bool b_(const json& v) { return v.is_boolean() && v.get<bool>(); }",
           "static int i_(const json& v) { return v.is_number() ? v.get<int>() : 0; }",
           "static double d_(const json& v) { return v.is_number() ? v.get<double>() : 0; }",
           "static const json& j_(const json& v) { return v; }",
           "template <class T> static void os_(T& t, const json& v, bool given) {",
           "    if (given) { if (v.is_null()) t = T(); else t = v.get<std::string>(); } }",
           "template <class T> static void ob_(T& t, const json& v, bool given) {",
           "    if (given) { if (v.is_null()) t = T(); else t = v.get<bool>(); } }",
           "template <class T> static void oi_(T& t, const json& v, bool given) {",
           "    if (given) { if (v.is_null()) t = T(); else t = v.get<int>(); } }",
           "template <class T> static void od_(T& t, const json& v, bool given) {",
           "    if (given) { if (v.is_null()) t = T(); else t = v.get<double>(); } }",
           "static void j_(json& t, const json& v, bool given) { if (given) t = v; }",
           "static bool given_(const json& a, size_t i, const json* kw, const char* n) {",
           "    size_t npos = a.size() - (kw ? 1 : 0);",
           "    return i < npos || (kw && kw->contains(n)); }", "",
           "json dispatch(openhab::OpenHABClient& c, const std::string& cls, const std::string& m,",
           "              const json& args) {",
           "    const json* kw = nullptr;",
           "    const json* last = args.empty() ? nullptr : &args.back();", ""]
    for fname, c, methods in load_classes(src):
        for m in methods.values():
            if m.private or m.stream:
                continue
            out.append(f'    if (cls == "{c.name}" && m == "{m.name}") {{')
            named = m.name in ("getItems", "getItem", "getItemPersistenceData")
            out.append(f"        kw = (last && last->is_object() && args.size() > {len(m.required)} && "
                       f"{'true' if (m.optional and named) else 'false'}) ? last : nullptr;")
            req = []
            for i, (n_, t, d, r) in enumerate(m.params):
                if r:
                    req.append(f"{conv[t]}(arg_(args, {i}, kw, \"{n_}\"))")
            if m.optional:
                out.append(f"        openhab::{c.name}::{m.args_struct} a;")
                for i, (n_, t, d, r) in enumerate(m.params):
                    if not r:
                        out.append(f"        {optconv[t]}(a.{cname(n_)}, arg_(args, {i}, kw, \"{n_}\"), "
                                   f"given_(args, {i}, kw, \"{n_}\"));")
                out.append(f"        return openhab::{c.name}(c).{m.name}({', '.join(req + ['a'])});")
            else:
                out.append(f"        return openhab::{c.name}(c).{m.name}({', '.join(req)});")
            out.append("    }")
    out += ["    (void)kw;", "    return json{{\"EXCEPTION\", \"no such method\"}};", "}", ""]
    return "\n".join(out)


def main():
    if sys.argv[1] == "--dispatch":
        print(dispatch_code(sys.argv[2]))
        return
    if sys.argv[1] == "--readme":
        print(readme_tables(sys.argv[2]))
        return
    generate(sys.argv[1], sys.argv[2])


if __name__ == "__main__":
    main()
