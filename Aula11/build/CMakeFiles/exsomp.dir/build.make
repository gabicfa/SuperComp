# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_SOURCE_DIR = /home/gabicfa/Documents/SuperComp/SuperComp/Aula11

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabicfa/Documents/SuperComp/SuperComp/Aula11/build

# Include any dependencies generated for this target.
include CMakeFiles/exsomp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exsomp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exsomp.dir/flags.make

CMakeFiles/exsomp.dir/exemplo-fs.cpp.o: CMakeFiles/exsomp.dir/flags.make
CMakeFiles/exsomp.dir/exemplo-fs.cpp.o: ../exemplo-fs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabicfa/Documents/SuperComp/SuperComp/Aula11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exsomp.dir/exemplo-fs.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exsomp.dir/exemplo-fs.cpp.o -c /home/gabicfa/Documents/SuperComp/SuperComp/Aula11/exemplo-fs.cpp

CMakeFiles/exsomp.dir/exemplo-fs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exsomp.dir/exemplo-fs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabicfa/Documents/SuperComp/SuperComp/Aula11/exemplo-fs.cpp > CMakeFiles/exsomp.dir/exemplo-fs.cpp.i

CMakeFiles/exsomp.dir/exemplo-fs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exsomp.dir/exemplo-fs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabicfa/Documents/SuperComp/SuperComp/Aula11/exemplo-fs.cpp -o CMakeFiles/exsomp.dir/exemplo-fs.cpp.s

# Object files for target exsomp
exsomp_OBJECTS = \
"CMakeFiles/exsomp.dir/exemplo-fs.cpp.o"

# External object files for target exsomp
exsomp_EXTERNAL_OBJECTS =

exsomp: CMakeFiles/exsomp.dir/exemplo-fs.cpp.o
exsomp: CMakeFiles/exsomp.dir/build.make
exsomp: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
exsomp: /usr/lib/x86_64-linux-gnu/libboost_system.so
exsomp: CMakeFiles/exsomp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabicfa/Documents/SuperComp/SuperComp/Aula11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exsomp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exsomp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exsomp.dir/build: exsomp

.PHONY : CMakeFiles/exsomp.dir/build

CMakeFiles/exsomp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exsomp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exsomp.dir/clean

CMakeFiles/exsomp.dir/depend:
	cd /home/gabicfa/Documents/SuperComp/SuperComp/Aula11/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabicfa/Documents/SuperComp/SuperComp/Aula11 /home/gabicfa/Documents/SuperComp/SuperComp/Aula11 /home/gabicfa/Documents/SuperComp/SuperComp/Aula11/build /home/gabicfa/Documents/SuperComp/SuperComp/Aula11/build /home/gabicfa/Documents/SuperComp/SuperComp/Aula11/build/CMakeFiles/exsomp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exsomp.dir/depend

