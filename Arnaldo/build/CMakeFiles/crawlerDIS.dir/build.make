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
CMAKE_SOURCE_DIR = /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/build

# Include any dependencies generated for this target.
include CMakeFiles/crawlerDIS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/crawlerDIS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crawlerDIS.dir/flags.make

CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.o: CMakeFiles/crawlerDIS.dir/flags.make
CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.o: ../crawlerDistribuido.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.o -c /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/crawlerDistribuido.cpp

CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/crawlerDistribuido.cpp > CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.i

CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/crawlerDistribuido.cpp -o CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.s

# Object files for target crawlerDIS
crawlerDIS_OBJECTS = \
"CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.o"

# External object files for target crawlerDIS
crawlerDIS_EXTERNAL_OBJECTS =

crawlerDIS: CMakeFiles/crawlerDIS.dir/crawlerDistribuido.cpp.o
crawlerDIS: CMakeFiles/crawlerDIS.dir/build.make
crawlerDIS: /usr/lib/openmpi/lib/libmpi_cxx.so
crawlerDIS: /usr/lib/openmpi/lib/libmpi.so
crawlerDIS: /usr/lib/openmpi/lib/libmpi_cxx.so
crawlerDIS: /usr/lib/openmpi/lib/libmpi.so
crawlerDIS: CMakeFiles/crawlerDIS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable crawlerDIS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crawlerDIS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crawlerDIS.dir/build: crawlerDIS

.PHONY : CMakeFiles/crawlerDIS.dir/build

CMakeFiles/crawlerDIS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crawlerDIS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crawlerDIS.dir/clean

CMakeFiles/crawlerDIS.dir/depend:
	cd /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/build /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/build /home/gabicfa/Documents/SuperComp/Projetos/Arnaldo/build/CMakeFiles/crawlerDIS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crawlerDIS.dir/depend

