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
CMAKE_SOURCE_DIR = /home/hp/EDA_Labs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hp/EDA_Labs/build

# Include any dependencies generated for this target.
include CMakeFiles/course_dimensionality.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/course_dimensionality.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/course_dimensionality.dir/flags.make

CMakeFiles/course_dimensionality.dir/source/main.cpp.o: CMakeFiles/course_dimensionality.dir/flags.make
CMakeFiles/course_dimensionality.dir/source/main.cpp.o: ../source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hp/EDA_Labs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/course_dimensionality.dir/source/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/course_dimensionality.dir/source/main.cpp.o -c /home/hp/EDA_Labs/source/main.cpp

CMakeFiles/course_dimensionality.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/course_dimensionality.dir/source/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hp/EDA_Labs/source/main.cpp > CMakeFiles/course_dimensionality.dir/source/main.cpp.i

CMakeFiles/course_dimensionality.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/course_dimensionality.dir/source/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hp/EDA_Labs/source/main.cpp -o CMakeFiles/course_dimensionality.dir/source/main.cpp.s

# Object files for target course_dimensionality
course_dimensionality_OBJECTS = \
"CMakeFiles/course_dimensionality.dir/source/main.cpp.o"

# External object files for target course_dimensionality
course_dimensionality_EXTERNAL_OBJECTS =

course_dimensionality: CMakeFiles/course_dimensionality.dir/source/main.cpp.o
course_dimensionality: CMakeFiles/course_dimensionality.dir/build.make
course_dimensionality: CMakeFiles/course_dimensionality.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hp/EDA_Labs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable course_dimensionality"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/course_dimensionality.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/course_dimensionality.dir/build: course_dimensionality

.PHONY : CMakeFiles/course_dimensionality.dir/build

CMakeFiles/course_dimensionality.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/course_dimensionality.dir/cmake_clean.cmake
.PHONY : CMakeFiles/course_dimensionality.dir/clean

CMakeFiles/course_dimensionality.dir/depend:
	cd /home/hp/EDA_Labs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hp/EDA_Labs /home/hp/EDA_Labs /home/hp/EDA_Labs/build /home/hp/EDA_Labs/build /home/hp/EDA_Labs/build/CMakeFiles/course_dimensionality.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/course_dimensionality.dir/depend

