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
include CMakeFiles/button.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/button.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/button.dir/flags.make

CMakeFiles/button.dir/tests/button.c.o: CMakeFiles/button.dir/flags.make
CMakeFiles/button.dir/tests/button.c.o: ../tests/button.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oussama/Desktop/projet_c_v6.0/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/button.dir/tests/button.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/button.dir/tests/button.c.o   -c /home/oussama/Desktop/projet_c_v6.0/tests/button.c

CMakeFiles/button.dir/tests/button.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/button.dir/tests/button.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/oussama/Desktop/projet_c_v6.0/tests/button.c > CMakeFiles/button.dir/tests/button.c.i

CMakeFiles/button.dir/tests/button.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/button.dir/tests/button.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/oussama/Desktop/projet_c_v6.0/tests/button.c -o CMakeFiles/button.dir/tests/button.c.s

# Object files for target button
button_OBJECTS = \
"CMakeFiles/button.dir/tests/button.c.o"

# External object files for target button
button_EXTERNAL_OBJECTS =

button: CMakeFiles/button.dir/tests/button.c.o
button: CMakeFiles/button.dir/build.make
button: libei.a
button: ../_x11/libeibase64.a
button: CMakeFiles/button.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oussama/Desktop/projet_c_v6.0/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable button"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/button.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/button.dir/build: button

.PHONY : CMakeFiles/button.dir/build

CMakeFiles/button.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/button.dir/cmake_clean.cmake
.PHONY : CMakeFiles/button.dir/clean

CMakeFiles/button.dir/depend:
	cd /home/oussama/Desktop/projet_c_v6.0/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oussama/Desktop/projet_c_v6.0 /home/oussama/Desktop/projet_c_v6.0 /home/oussama/Desktop/projet_c_v6.0/cmake /home/oussama/Desktop/projet_c_v6.0/cmake /home/oussama/Desktop/projet_c_v6.0/cmake/CMakeFiles/button.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/button.dir/depend

