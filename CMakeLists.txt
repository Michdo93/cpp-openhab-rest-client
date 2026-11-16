cmake_minimum_required(VERSION 3.16)
project(OpenHABRestClientCpp VERSION 2.0.0 LANGUAGES CXX)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(OPENHAB_TOP_LEVEL ON)
else()
  set(OPENHAB_TOP_LEVEL OFF)
endif()
option(OPENHAB_BUILD_TESTS "Build the tests" ${OPENHAB_TOP_LEVEL})
# Install rules only for a top-level build: a project that pulls the library in with
# FetchContent/add_subdirectory links it statically and installs nothing of it
option(OPENHAB_INSTALL "Generate install rules" ${OPENHAB_TOP_LEVEL})

# ── Dependencies: libcurl and nlohmann/json (installed package or download) ──
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 QUIET)
set(OPENHAB_JSON_BUNDLED OFF)
if(NOT nlohmann_json_FOUND)
  include(FetchContent)
  FetchContent_Declare(nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
  set(JSON_Install ${OPENHAB_INSTALL} CACHE INTERNAL "")
  FetchContent_MakeAvailable(nlohmann_json)
  set(OPENHAB_JSON_BUNDLED ON)
  message(STATUS "nlohmann/json: downloaded (v3.11.3)")
endif()

# ── Sources ───────────────────────────────────────────────────────────────────
file(GLOB OPENHAB_API_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/api/*.cpp)
set(LIB_SOURCES
  src/OpenHABClient.cpp
  src/EventStream.cpp
  src/py_rt.cpp
  ${OPENHAB_API_SOURCES})

set(PLATFORM_LIBS "")
if(WIN32)
  list(APPEND PLATFORM_LIBS ws2_32)
else()
  find_package(Threads REQUIRED)
  list(APPEND PLATFORM_LIBS Threads::Threads)
endif()

function(openhab_setup target)
  target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
  target_link_libraries(${target} PUBLIC nlohmann_json::nlohmann_json
                                  PRIVATE CURL::libcurl ${PLATFORM_LIBS})
  target_compile_features(${target} PUBLIC cxx_std_17)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wno-unused-parameter)
  endif()
endfunction()

# ── Shared and static library (from the same object files) ──────────────────
add_library(openhab_rest_client_cpp_obj OBJECT ${LIB_SOURCES})
openhab_setup(openhab_rest_client_cpp_obj)
target_compile_definitions(openhab_rest_client_cpp_obj PRIVATE OPENHAB_BUILDING_DLL)
set_target_properties(openhab_rest_client_cpp_obj PROPERTIES
  POSITION_INDEPENDENT_CODE ON CXX_VISIBILITY_PRESET hidden)

add_library(openhab_rest_client_cpp SHARED $<TARGET_OBJECTS:openhab_rest_client_cpp_obj>)
openhab_setup(openhab_rest_client_cpp)
set_target_properties(openhab_rest_client_cpp PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 2)
if(WIN32)
  set_target_properties(openhab_rest_client_cpp PROPERTIES PREFIX "")
endif()

add_library(openhab_rest_client_cpp_static STATIC $<TARGET_OBJECTS:openhab_rest_client_cpp_obj>)
openhab_setup(openhab_rest_client_cpp_static)
target_compile_definitions(openhab_rest_client_cpp_static PUBLIC OPENHAB_STATIC)
if(NOT WIN32)
  set_target_properties(openhab_rest_client_cpp_static PROPERTIES OUTPUT_NAME openhab_rest_client_cpp)
endif()

# The same target names in the build tree and after find_package():
#   openhab::rest_client_cpp (static), openhab::rest_client_cpp_shared
set_target_properties(openhab_rest_client_cpp_static PROPERTIES EXPORT_NAME rest_client_cpp)
set_target_properties(openhab_rest_client_cpp PROPERTIES EXPORT_NAME rest_client_cpp_shared)
add_library(openhab::rest_client_cpp ALIAS openhab_rest_client_cpp_static)
add_library(openhab::rest_client_cpp_shared ALIAS openhab_rest_client_cpp)

# ── Tests ─────────────────────────────────────────────────────────────────────
if(OPENHAB_BUILD_TESTS AND NOT CMAKE_CROSSCOMPILING)
  enable_testing()
  add_executable(openhab_unit_test test/unit_test.cpp)
  target_link_libraries(openhab_unit_test PRIVATE openhab_rest_client_cpp_static)
  add_test(NAME unit COMMAND openhab_unit_test)
  add_executable(openhab_integration_test test/integration_test.cpp)
  target_link_libraries(openhab_integration_test PRIVATE openhab_rest_client_cpp_static)
  add_test(NAME integration COMMAND openhab_integration_test)
  set_tests_properties(integration PROPERTIES SKIP_RETURN_CODE 77)
  # C++20: argument structs with designated initializers
  add_executable(openhab_cpp20_test test/cpp20_test.cpp)
  set_target_properties(openhab_cpp20_test PROPERTIES CXX_STANDARD 20)
  target_link_libraries(openhab_cpp20_test PRIVATE openhab_rest_client_cpp_static)
  add_test(NAME cpp20 COMMAND openhab_cpp20_test)
endif()

# ── Install (find_package(OpenHABRestClientCpp) and pkg-config) ──────────────
if(OPENHAB_INSTALL)
  include(GNUInstallDirs)
  include(CMakePackageConfigHelpers)
  install(TARGETS openhab_rest_client_cpp openhab_rest_client_cpp_static
    EXPORT OpenHABRestClientCppTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  install(EXPORT OpenHABRestClientCppTargets NAMESPACE openhab::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenHABRestClientCpp)
  configure_package_config_file(cmake/OpenHABRestClientCppConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientCppConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenHABRestClientCpp)
  write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientCppConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)
  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientCppConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientCppConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenHABRestClientCpp)
  configure_file(cmake/openhab_rest_client_cpp.pc.in openhab_rest_client_cpp.pc @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/openhab_rest_client_cpp.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()

message(STATUS "cpp-openhab-rest-client ${PROJECT_VERSION}")
