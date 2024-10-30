cmake_minimum_required(VERSION 3.11)

project(http_server CXX)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

add_executable(http_server src/main.cpp src/http_server.h src/http_server.cpp src/body_types.cpp src/body_types.h src/boost_json.cpp src/request_handler.h
  src/resp_maker.h src/sdk.h)

set(THREAD_PREFER_PTHREAD_FLAG_ON)
find_package(Threads REQUIRED)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
  set(SYSTEM_LIBS -lstdc++)
else()
  set(SYSTEM_LIBS)
endif()

target_include_directories(http_server PRIVATE CONAN_PKG::boost)
target_link_libraries(http_server PRIVATE Threads::Threads CONAN_PKG::boost)

target_link_libraries(http_server ${SYSTEM_LIBS})
