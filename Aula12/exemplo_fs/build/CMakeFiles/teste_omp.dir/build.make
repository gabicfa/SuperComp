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
CMAKE_SOURCE_DIR = /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/build

# Include any dependencies generated for this target.
include CMakeFiles/teste_omp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/teste_omp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/teste_omp.dir/flags.make

CMakeFiles/teste_omp.dir/teste_omp.cpp.o: CMakeFiles/teste_omp.dir/flags.make
CMakeFiles/teste_omp.dir/teste_omp.cpp.o: ../teste_omp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/teste_omp.dir/teste_omp.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-5  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/teste_omp.dir/teste_omp.cpp.o -c /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/teste_omp.cpp

CMakeFiles/teste_omp.dir/teste_omp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/teste_omp.dir/teste_omp.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-5 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/teste_omp.cpp > CMakeFiles/teste_omp.dir/teste_omp.cpp.i

CMakeFiles/teste_omp.dir/teste_omp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/teste_omp.dir/teste_omp.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-5 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/teste_omp.cpp -o CMakeFiles/teste_omp.dir/teste_omp.cpp.s

# Object files for target teste_omp
teste_omp_OBJECTS = \
"CMakeFiles/teste_omp.dir/teste_omp.cpp.o"

# External object files for target teste_omp
teste_omp_EXTERNAL_OBJECTS =

teste_omp: CMakeFiles/teste_omp.dir/teste_omp.cpp.o
teste_omp: CMakeFiles/teste_omp.dir/build.make
teste_omp: /usr/lib/gcc/x86_64-linux-gnu/5/libgomp.so
teste_omp: /usr/lib/x86_64-linux-gnu/libpthread.so
teste_omp: CMakeFiles/teste_omp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable teste_omp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/teste_omp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/teste_omp.dir/build: teste_omp

.PHONY : CMakeFiles/teste_omp.dir/build

CMakeFiles/teste_omp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/teste_omp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/teste_omp.dir/clean

CMakeFiles/teste_omp.dir/depend:
	cd /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/build /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/build /home/gabicfa/Documents/SuperComp/SuperComp/Aula12/exemplo_fs/build/CMakeFiles/teste_omp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/teste_omp.dir/depend

