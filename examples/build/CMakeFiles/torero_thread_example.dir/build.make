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
include CMakeFiles/torero_thread_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/torero_thread_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/torero_thread_example.dir/flags.make

CMakeFiles/torero_thread_example.dir/main.cpp.o: CMakeFiles/torero_thread_example.dir/flags.make
CMakeFiles/torero_thread_example.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/torero_thread_example.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/torero_thread_example.dir/main.cpp.o -c /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/main.cpp

CMakeFiles/torero_thread_example.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/torero_thread_example.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/main.cpp > CMakeFiles/torero_thread_example.dir/main.cpp.i

CMakeFiles/torero_thread_example.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/torero_thread_example.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/main.cpp -o CMakeFiles/torero_thread_example.dir/main.cpp.s

# Object files for target torero_thread_example
torero_thread_example_OBJECTS = \
"CMakeFiles/torero_thread_example.dir/main.cpp.o"

# External object files for target torero_thread_example
torero_thread_example_EXTERNAL_OBJECTS =

torero_thread_example: CMakeFiles/torero_thread_example.dir/main.cpp.o
torero_thread_example: CMakeFiles/torero_thread_example.dir/build.make
torero_thread_example: libs/libtorero_threads.a
torero_thread_example: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
torero_thread_example: /usr/lib/x86_64-linux-gnu/libboost_system.so
torero_thread_example: /usr/lib/x86_64-linux-gnu/libboost_thread.so
torero_thread_example: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
torero_thread_example: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
torero_thread_example: CMakeFiles/torero_thread_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable torero_thread_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/torero_thread_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/torero_thread_example.dir/build: torero_thread_example

.PHONY : CMakeFiles/torero_thread_example.dir/build

CMakeFiles/torero_thread_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/torero_thread_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/torero_thread_example.dir/clean

CMakeFiles/torero_thread_example.dir/depend:
	cd /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build /mnt/shared/Users/framirez/Documents/Qt/multithreading/examples/build/CMakeFiles/torero_thread_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/torero_thread_example.dir/depend
