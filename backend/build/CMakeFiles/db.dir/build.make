# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/enxsz/PetProjects/Enterprise-HR-Database/backend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/enxsz/PetProjects/Enterprise-HR-Database/backend/build

# Include any dependencies generated for this target.
include CMakeFiles/db.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/db.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/db.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/db.dir/flags.make

CMakeFiles/db.dir/src/app/use_cases_impl.cpp.o: CMakeFiles/db.dir/flags.make
CMakeFiles/db.dir/src/app/use_cases_impl.cpp.o: ../src/app/use_cases_impl.cpp
CMakeFiles/db.dir/src/app/use_cases_impl.cpp.o: CMakeFiles/db.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/enxsz/PetProjects/Enterprise-HR-Database/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/db.dir/src/app/use_cases_impl.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/db.dir/src/app/use_cases_impl.cpp.o -MF CMakeFiles/db.dir/src/app/use_cases_impl.cpp.o.d -o CMakeFiles/db.dir/src/app/use_cases_impl.cpp.o -c /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/app/use_cases_impl.cpp

CMakeFiles/db.dir/src/app/use_cases_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/db.dir/src/app/use_cases_impl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/app/use_cases_impl.cpp > CMakeFiles/db.dir/src/app/use_cases_impl.cpp.i

CMakeFiles/db.dir/src/app/use_cases_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/db.dir/src/app/use_cases_impl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/app/use_cases_impl.cpp -o CMakeFiles/db.dir/src/app/use_cases_impl.cpp.s

CMakeFiles/db.dir/src/db.cpp.o: CMakeFiles/db.dir/flags.make
CMakeFiles/db.dir/src/db.cpp.o: ../src/db.cpp
CMakeFiles/db.dir/src/db.cpp.o: CMakeFiles/db.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/enxsz/PetProjects/Enterprise-HR-Database/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/db.dir/src/db.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/db.dir/src/db.cpp.o -MF CMakeFiles/db.dir/src/db.cpp.o.d -o CMakeFiles/db.dir/src/db.cpp.o -c /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/db.cpp

CMakeFiles/db.dir/src/db.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/db.dir/src/db.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/db.cpp > CMakeFiles/db.dir/src/db.cpp.i

CMakeFiles/db.dir/src/db.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/db.dir/src/db.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/db.cpp -o CMakeFiles/db.dir/src/db.cpp.s

CMakeFiles/db.dir/src/main.cpp.o: CMakeFiles/db.dir/flags.make
CMakeFiles/db.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/db.dir/src/main.cpp.o: CMakeFiles/db.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/enxsz/PetProjects/Enterprise-HR-Database/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/db.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/db.dir/src/main.cpp.o -MF CMakeFiles/db.dir/src/main.cpp.o.d -o CMakeFiles/db.dir/src/main.cpp.o -c /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/main.cpp

CMakeFiles/db.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/db.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/main.cpp > CMakeFiles/db.dir/src/main.cpp.i

CMakeFiles/db.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/db.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/main.cpp -o CMakeFiles/db.dir/src/main.cpp.s

CMakeFiles/db.dir/src/postgres/postgres.cpp.o: CMakeFiles/db.dir/flags.make
CMakeFiles/db.dir/src/postgres/postgres.cpp.o: ../src/postgres/postgres.cpp
CMakeFiles/db.dir/src/postgres/postgres.cpp.o: CMakeFiles/db.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/enxsz/PetProjects/Enterprise-HR-Database/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/db.dir/src/postgres/postgres.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/db.dir/src/postgres/postgres.cpp.o -MF CMakeFiles/db.dir/src/postgres/postgres.cpp.o.d -o CMakeFiles/db.dir/src/postgres/postgres.cpp.o -c /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/postgres/postgres.cpp

CMakeFiles/db.dir/src/postgres/postgres.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/db.dir/src/postgres/postgres.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/postgres/postgres.cpp > CMakeFiles/db.dir/src/postgres/postgres.cpp.i

CMakeFiles/db.dir/src/postgres/postgres.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/db.dir/src/postgres/postgres.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/enxsz/PetProjects/Enterprise-HR-Database/backend/src/postgres/postgres.cpp -o CMakeFiles/db.dir/src/postgres/postgres.cpp.s

# Object files for target db
db_OBJECTS = \
"CMakeFiles/db.dir/src/app/use_cases_impl.cpp.o" \
"CMakeFiles/db.dir/src/db.cpp.o" \
"CMakeFiles/db.dir/src/main.cpp.o" \
"CMakeFiles/db.dir/src/postgres/postgres.cpp.o"

# External object files for target db
db_EXTERNAL_OBJECTS =

db: CMakeFiles/db.dir/src/app/use_cases_impl.cpp.o
db: CMakeFiles/db.dir/src/db.cpp.o
db: CMakeFiles/db.dir/src/main.cpp.o
db: CMakeFiles/db.dir/src/postgres/postgres.cpp.o
db: CMakeFiles/db.dir/build.make
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_contract.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_coroutine.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_fiber_numa.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_fiber.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_context.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_graph.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_iostreams.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_json.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_locale.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_log_setup.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_log.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_math_c99.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_math_c99f.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_math_c99l.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_math_tr1.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_math_tr1f.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_math_tr1l.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_nowide.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_program_options.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_random.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_regex.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_stacktrace_addr2line.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_stacktrace_backtrace.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_stacktrace_basic.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_stacktrace_noop.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_timer.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_type_erasure.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_thread.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_chrono.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_container.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_date_time.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_unit_test_framework.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_prg_exec_monitor.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_test_exec_monitor.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_exception.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_wave.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_filesystem.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_atomic.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_wserialization.a
db: /home/enxsz/.conan/data/boost/1.78.0/_/_/package/dc8aedd23a0f0a773a5fcdcfe1ae3e89c4205978/lib/libboost_serialization.a
db: /home/enxsz/.conan/data/zlib/1.3/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/lib/libz.a
db: /home/enxsz/.conan/data/bzip2/1.0.8/_/_/package/c32092bf4d4bb47cf962af898e02823f499b017e/lib/libbz2.a
db: /home/enxsz/.conan/data/libbacktrace/cci.20210118/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/lib/libbacktrace.a
db: /home/enxsz/.conan/data/libpqxx/7.7.4/_/_/package/04cbdfff4f57b797b6cf60c443f251cb70622a37/lib/libpqxx.a
db: /home/enxsz/.conan/data/libpq/14.5/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/lib/libpq.a
db: /home/enxsz/.conan/data/libpq/14.5/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/lib/libpgcommon.a
db: /home/enxsz/.conan/data/libpq/14.5/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/lib/libpgcommon_shlib.a
db: /home/enxsz/.conan/data/libpq/14.5/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/lib/libpgport.a
db: /home/enxsz/.conan/data/libpq/14.5/_/_/package/dfbe50feef7f3c6223a476cd5aeadb687084a646/lib/libpgport_shlib.a
db: CMakeFiles/db.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/enxsz/PetProjects/Enterprise-HR-Database/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable db"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/db.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/db.dir/build: db
.PHONY : CMakeFiles/db.dir/build

CMakeFiles/db.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/db.dir/cmake_clean.cmake
.PHONY : CMakeFiles/db.dir/clean

CMakeFiles/db.dir/depend:
	cd /home/enxsz/PetProjects/Enterprise-HR-Database/backend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/enxsz/PetProjects/Enterprise-HR-Database/backend /home/enxsz/PetProjects/Enterprise-HR-Database/backend /home/enxsz/PetProjects/Enterprise-HR-Database/backend/build /home/enxsz/PetProjects/Enterprise-HR-Database/backend/build /home/enxsz/PetProjects/Enterprise-HR-Database/backend/build/CMakeFiles/db.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/db.dir/depend
