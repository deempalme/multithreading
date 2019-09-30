# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build

# Include any dependencies generated for this target.
include libs/CMakeFiles/torero_threads.dir/depend.make

# Include the progress variables for this target.
include libs/CMakeFiles/torero_threads.dir/progress.make

# Include the compile flags for this target's objects.
include libs/CMakeFiles/torero_threads.dir/flags.make

libs/CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.o: libs/CMakeFiles/torero_threads.dir/flags.make
libs/CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.o: ../../src/torero/cpu/threads.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.o"
	cd /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/libs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.o -c /mnt/shared/Users/framirez/Documents/Qt/multithreading/src/torero/cpu/threads.cpp

libs/CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.i"
	cd /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/libs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/shared/Users/framirez/Documents/Qt/multithreading/src/torero/cpu/threads.cpp > CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.i

libs/CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.s"
	cd /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/libs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/shared/Users/framirez/Documents/Qt/multithreading/src/torero/cpu/threads.cpp -o CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.s

# Object files for target torero_threads
torero_threads_OBJECTS = \
"CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.o"

# External object files for target torero_threads
torero_threads_EXTERNAL_OBJECTS =

libs/libtorero_threads.a: libs/CMakeFiles/torero_threads.dir/src/torero/cpu/threads.cpp.o
libs/libtorero_threads.a: libs/CMakeFiles/torero_threads.dir/build.make
libs/libtorero_threads.a: libs/CMakeFiles/torero_threads.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtorero_threads.a"
	cd /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/libs && $(CMAKE_COMMAND) -P CMakeFiles/torero_threads.dir/cmake_clean_target.cmake
	cd /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/libs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/torero_threads.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/CMakeFiles/torero_threads.dir/build: libs/libtorero_threads.a

.PHONY : libs/CMakeFiles/torero_threads.dir/build

libs/CMakeFiles/torero_threads.dir/clean:
	cd /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/libs && $(CMAKE_COMMAND) -P CMakeFiles/torero_threads.dir/cmake_clean.cmake
.PHONY : libs/CMakeFiles/torero_threads.dir/clean

libs/CMakeFiles/torero_threads.dir/depend:
	cd /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples /mnt/shared/Users/framirez/Documents/Qt/multithreading /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/libs /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/libs/CMakeFiles/torero_threads.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/CMakeFiles/torero_threads.dir/depend
