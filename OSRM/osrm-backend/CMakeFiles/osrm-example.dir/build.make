# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend/example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend

# Include any dependencies generated for this target.
include CMakeFiles/osrm-example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/osrm-example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/osrm-example.dir/flags.make

CMakeFiles/osrm-example.dir/example.cpp.o: CMakeFiles/osrm-example.dir/flags.make
CMakeFiles/osrm-example.dir/example.cpp.o: example/example.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/osrm-example.dir/example.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/osrm-example.dir/example.cpp.o -c /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend/example/example.cpp

CMakeFiles/osrm-example.dir/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/osrm-example.dir/example.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend/example/example.cpp > CMakeFiles/osrm-example.dir/example.cpp.i

CMakeFiles/osrm-example.dir/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/osrm-example.dir/example.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend/example/example.cpp -o CMakeFiles/osrm-example.dir/example.cpp.s

CMakeFiles/osrm-example.dir/example.cpp.o.requires:

.PHONY : CMakeFiles/osrm-example.dir/example.cpp.o.requires

CMakeFiles/osrm-example.dir/example.cpp.o.provides: CMakeFiles/osrm-example.dir/example.cpp.o.requires
	$(MAKE) -f CMakeFiles/osrm-example.dir/build.make CMakeFiles/osrm-example.dir/example.cpp.o.provides.build
.PHONY : CMakeFiles/osrm-example.dir/example.cpp.o.provides

CMakeFiles/osrm-example.dir/example.cpp.o.provides.build: CMakeFiles/osrm-example.dir/example.cpp.o


# Object files for target osrm-example
osrm__example_OBJECTS = \
"CMakeFiles/osrm-example.dir/example.cpp.o"

# External object files for target osrm-example
osrm__example_EXTERNAL_OBJECTS =

osrm-example: CMakeFiles/osrm-example.dir/example.cpp.o
osrm-example: CMakeFiles/osrm-example.dir/build.make
osrm-example: /usr/lib/x86_64-linux-gnu/libboost_regex.so
osrm-example: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
osrm-example: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
osrm-example: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
osrm-example: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
osrm-example: /usr/lib/x86_64-linux-gnu/libboost_thread.so
osrm-example: /usr/lib/x86_64-linux-gnu/libboost_system.so
osrm-example: /usr/lib/x86_64-linux-gnu/libtbb.so
osrm-example: /usr/lib/x86_64-linux-gnu/libtbbmalloc.so
osrm-example: /usr/lib/x86_64-linux-gnu/libz.so
osrm-example: CMakeFiles/osrm-example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable osrm-example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/osrm-example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/osrm-example.dir/build: osrm-example

.PHONY : CMakeFiles/osrm-example.dir/build

CMakeFiles/osrm-example.dir/requires: CMakeFiles/osrm-example.dir/example.cpp.o.requires

.PHONY : CMakeFiles/osrm-example.dir/requires

CMakeFiles/osrm-example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/osrm-example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/osrm-example.dir/clean

CMakeFiles/osrm-example.dir/depend:
	cd /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend/example /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend/example /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend /home/arnaud/Bureau/PDM/OSRM/Master-Thesis/OSRM/osrm-backend/CMakeFiles/osrm-example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/osrm-example.dir/depend
