cmake_minimum_required(VERSION 3.16)
project(OpenHABRestClient VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ── Dependencies ──────────────────────────────────────────────────────────────

find_package(CURL REQUIRED)

find_package(nlohmann_json 3.2.0 QUIET)
if(NOT nlohmann_json_FOUND)
  include(FetchContent)
  FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
  FetchContent_MakeAvailable(json)
endif()

# ── Library sources ───────────────────────────────────────────────────────────

set(LIB_SOURCES
  src/OpenHABClient.cpp
  src/Items.cpp
  src/Things.cpp
  src/Rules.cpp
  src/Events.cpp
  src/Actions.cpp
)

# ── Shared library ────────────────────────────────────────────────────────────

add_library(openhab_rest_client SHARED ${LIB_SOURCES})
target_include_directories(openhab_rest_client PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(openhab_rest_client
  PRIVATE ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)
set_target_properties(openhab_rest_client PROPERTIES
  VERSION   ${PROJECT_VERSION}
  SOVERSION 1)

# ── Static library ────────────────────────────────────────────────────────────

add_library(openhab_rest_client_static STATIC ${LIB_SOURCES})
set_target_properties(openhab_rest_client_static PROPERTIES
  OUTPUT_NAME openhab_rest_client)
target_include_directories(openhab_rest_client_static PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(openhab_rest_client_static
  PRIVATE ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)

# ── Test executable ───────────────────────────────────────────────────────────

add_executable(openhab_test test/test.cpp)
target_link_libraries(openhab_test PRIVATE
  openhab_rest_client_static ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)

# ── Install ───────────────────────────────────────────────────────────────────

include(GNUInstallDirs)
install(TARGETS openhab_rest_client openhab_rest_client_static
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/openhab DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# ── CMake package config (for find_package support) ──────────────────────────

include(CMakePackageConfigHelpers)
configure_package_config_file(
  cmake/OpenHABRestClientConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenHABRestClient)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenHABRestClient)

message(STATUS "──────────────────────────────────────────")
message(STATUS " OpenHABRestClient ${PROJECT_VERSION}")
message(STATUS " CURL: ${CURL_LIBRARIES}")
message(STATUS "──────────────────────────────────────────")
