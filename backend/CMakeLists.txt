cmake_minimum_required(VERSION 3.11)

project(db CXX)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

add_executable(db src/app/use_cases.h src/app/use_cases_impl.cpp src/app/use_cases_impl.h src/connection_pool.h src/db.h src/db.cpp src/domain/department.h
               src/domain/department_fwd.h src/main.cpp src/postgres/postgres.h src/postgres/postgres.cpp src/ui/view.h src/domain/worker.h src/domain/job_title.h
               src/domain/job_title_fwd.h src/domain/time_sheet.h src/domain/time_sheet_fwd.h src/domain/staffing_table.h src/domain/staffing_table_fwd.h)

set(THREAD_PREFER_PTHREAD_FLAG_ON)
find_package(Threads REQUIRED)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
  set(SYSTEM_LIBS -lstdc++)
else()
  set(SYSTEM_LIBS)
endif()

target_include_directories(db PRIVATE CONAN_PKG::boost CONAN_PKG:libpqxx)
target_link_libraries(db PRIVATE Threads::Threads CONAN_PKG::boost CONAN_PKG::libpqxx)

target_link_libraries(db ${SYSTEM_LIBS})
