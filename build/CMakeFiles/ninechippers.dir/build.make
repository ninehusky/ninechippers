# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.20.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.20.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/niney/Desktop/code/ninechippers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/niney/Desktop/code/ninechippers/build

# Include any dependencies generated for this target.
include CMakeFiles/ninechippers.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ninechippers.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ninechippers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ninechippers.dir/flags.make

CMakeFiles/ninechippers.dir/src/hello.c.o: CMakeFiles/ninechippers.dir/flags.make
CMakeFiles/ninechippers.dir/src/hello.c.o: ../src/hello.c
CMakeFiles/ninechippers.dir/src/hello.c.o: CMakeFiles/ninechippers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/niney/Desktop/code/ninechippers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ninechippers.dir/src/hello.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ninechippers.dir/src/hello.c.o -MF CMakeFiles/ninechippers.dir/src/hello.c.o.d -o CMakeFiles/ninechippers.dir/src/hello.c.o -c /Users/niney/Desktop/code/ninechippers/src/hello.c

CMakeFiles/ninechippers.dir/src/hello.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ninechippers.dir/src/hello.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/niney/Desktop/code/ninechippers/src/hello.c > CMakeFiles/ninechippers.dir/src/hello.c.i

CMakeFiles/ninechippers.dir/src/hello.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ninechippers.dir/src/hello.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/niney/Desktop/code/ninechippers/src/hello.c -o CMakeFiles/ninechippers.dir/src/hello.c.s

CMakeFiles/ninechippers.dir/src/square.c.o: CMakeFiles/ninechippers.dir/flags.make
CMakeFiles/ninechippers.dir/src/square.c.o: ../src/square.c
CMakeFiles/ninechippers.dir/src/square.c.o: CMakeFiles/ninechippers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/niney/Desktop/code/ninechippers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ninechippers.dir/src/square.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ninechippers.dir/src/square.c.o -MF CMakeFiles/ninechippers.dir/src/square.c.o.d -o CMakeFiles/ninechippers.dir/src/square.c.o -c /Users/niney/Desktop/code/ninechippers/src/square.c

CMakeFiles/ninechippers.dir/src/square.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ninechippers.dir/src/square.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/niney/Desktop/code/ninechippers/src/square.c > CMakeFiles/ninechippers.dir/src/square.c.i

CMakeFiles/ninechippers.dir/src/square.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ninechippers.dir/src/square.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/niney/Desktop/code/ninechippers/src/square.c -o CMakeFiles/ninechippers.dir/src/square.c.s

# Object files for target ninechippers
ninechippers_OBJECTS = \
"CMakeFiles/ninechippers.dir/src/hello.c.o" \
"CMakeFiles/ninechippers.dir/src/square.c.o"

# External object files for target ninechippers
ninechippers_EXTERNAL_OBJECTS =

ninechippers: CMakeFiles/ninechippers.dir/src/hello.c.o
ninechippers: CMakeFiles/ninechippers.dir/src/square.c.o
ninechippers: CMakeFiles/ninechippers.dir/build.make
ninechippers: CMakeFiles/ninechippers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/niney/Desktop/code/ninechippers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ninechippers"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ninechippers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ninechippers.dir/build: ninechippers
.PHONY : CMakeFiles/ninechippers.dir/build

CMakeFiles/ninechippers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ninechippers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ninechippers.dir/clean

CMakeFiles/ninechippers.dir/depend:
	cd /Users/niney/Desktop/code/ninechippers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/niney/Desktop/code/ninechippers /Users/niney/Desktop/code/ninechippers /Users/niney/Desktop/code/ninechippers/build /Users/niney/Desktop/code/ninechippers/build /Users/niney/Desktop/code/ninechippers/build/CMakeFiles/ninechippers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ninechippers.dir/depend
