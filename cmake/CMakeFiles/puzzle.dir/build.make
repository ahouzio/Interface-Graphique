# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oussama/Desktop/projet_c_v6.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oussama/Desktop/projet_c_v6.0/cmake

# Include any dependencies generated for this target.
include CMakeFiles/puzzle.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/puzzle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/puzzle.dir/flags.make

CMakeFiles/puzzle.dir/tests/puzzle.c.o: CMakeFiles/puzzle.dir/flags.make
CMakeFiles/puzzle.dir/tests/puzzle.c.o: ../tests/puzzle.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oussama/Desktop/projet_c_v6.0/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/puzzle.dir/tests/puzzle.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/puzzle.dir/tests/puzzle.c.o   -c /home/oussama/Desktop/projet_c_v6.0/tests/puzzle.c

CMakeFiles/puzzle.dir/tests/puzzle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/puzzle.dir/tests/puzzle.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/oussama/Desktop/projet_c_v6.0/tests/puzzle.c > CMakeFiles/puzzle.dir/tests/puzzle.c.i

CMakeFiles/puzzle.dir/tests/puzzle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/puzzle.dir/tests/puzzle.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/oussama/Desktop/projet_c_v6.0/tests/puzzle.c -o CMakeFiles/puzzle.dir/tests/puzzle.c.s

# Object files for target puzzle
puzzle_OBJECTS = \
"CMakeFiles/puzzle.dir/tests/puzzle.c.o"

# External object files for target puzzle
puzzle_EXTERNAL_OBJECTS =

puzzle: CMakeFiles/puzzle.dir/tests/puzzle.c.o
puzzle: CMakeFiles/puzzle.dir/build.make
puzzle: libei.a
puzzle: ../_x11/libeibase64.a
puzzle: CMakeFiles/puzzle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oussama/Desktop/projet_c_v6.0/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable puzzle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/puzzle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/puzzle.dir/build: puzzle

.PHONY : CMakeFiles/puzzle.dir/build

CMakeFiles/puzzle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/puzzle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/puzzle.dir/clean

CMakeFiles/puzzle.dir/depend:
	cd /home/oussama/Desktop/projet_c_v6.0/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oussama/Desktop/projet_c_v6.0 /home/oussama/Desktop/projet_c_v6.0 /home/oussama/Desktop/projet_c_v6.0/cmake /home/oussama/Desktop/projet_c_v6.0/cmake /home/oussama/Desktop/projet_c_v6.0/cmake/CMakeFiles/puzzle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/puzzle.dir/depend

