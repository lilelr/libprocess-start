# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /home/lilelr/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/lilelr/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lilelr/open-source/bak_mesos-1.3.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug

# Include any dependencies generated for this target.
include src/examples/CMakeFiles/examplemodule.dir/depend.make

# Include the progress variables for this target.
include src/examples/CMakeFiles/examplemodule.dir/progress.make

# Include the compile flags for this target's objects.
include src/examples/CMakeFiles/examplemodule.dir/flags.make

src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o: src/examples/CMakeFiles/examplemodule.dir/flags.make
src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o: ../src/examples/example_module_impl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o"
	cd /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug/src/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/examplemodule.dir/example_module_impl.cpp.o -c /home/lilelr/open-source/bak_mesos-1.3.2/src/examples/example_module_impl.cpp

src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/examplemodule.dir/example_module_impl.cpp.i"
	cd /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug/src/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lilelr/open-source/bak_mesos-1.3.2/src/examples/example_module_impl.cpp > CMakeFiles/examplemodule.dir/example_module_impl.cpp.i

src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/examplemodule.dir/example_module_impl.cpp.s"
	cd /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug/src/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lilelr/open-source/bak_mesos-1.3.2/src/examples/example_module_impl.cpp -o CMakeFiles/examplemodule.dir/example_module_impl.cpp.s

src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o.requires:

.PHONY : src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o.requires

src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o.provides: src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o.requires
	$(MAKE) -f src/examples/CMakeFiles/examplemodule.dir/build.make src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o.provides.build
.PHONY : src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o.provides

src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o.provides.build: src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o


# Object files for target examplemodule
examplemodule_OBJECTS = \
"CMakeFiles/examplemodule.dir/example_module_impl.cpp.o"

# External object files for target examplemodule
examplemodule_EXTERNAL_OBJECTS =

src/.libs/libexamplemodule.so: src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o
src/.libs/libexamplemodule.so: src/examples/CMakeFiles/examplemodule.dir/build.make
src/.libs/libexamplemodule.so: src/.libs/libmesos-1.3.2.so.1.3.2
src/.libs/libexamplemodule.so: src/libmesos-protobufs.so
src/.libs/libexamplemodule.so: 3rdparty/zookeeper-3.4.8/src/zookeeper-3.4.8/src/c/lib/libzookeeper_mt.a
src/.libs/libexamplemodule.so: 3rdparty/libprocess/src/libprocess-0.0.1.so.0.0.1
src/.libs/libexamplemodule.so: /usr/lib/x86_64-linux-gnu/libapr-1.so
src/.libs/libexamplemodule.so: /usr/lib/x86_64-linux-gnu/libsvn_delta-1.so
src/.libs/libexamplemodule.so: /usr/lib/x86_64-linux-gnu/libsvn_diff-1.so
src/.libs/libexamplemodule.so: /usr/lib/x86_64-linux-gnu/libsvn_subr-1.so
src/.libs/libexamplemodule.so: 3rdparty/leveldb-1.19/src/leveldb-1.19/out-static/libleveldb.a
src/.libs/libexamplemodule.so: /usr/lib/x86_64-linux-gnu/libz.so
src/.libs/libexamplemodule.so: src/examples/CMakeFiles/examplemodule.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../.libs/libexamplemodule.so"
	cd /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug/src/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/examplemodule.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/examples/CMakeFiles/examplemodule.dir/build: src/.libs/libexamplemodule.so

.PHONY : src/examples/CMakeFiles/examplemodule.dir/build

src/examples/CMakeFiles/examplemodule.dir/requires: src/examples/CMakeFiles/examplemodule.dir/example_module_impl.cpp.o.requires

.PHONY : src/examples/CMakeFiles/examplemodule.dir/requires

src/examples/CMakeFiles/examplemodule.dir/clean:
	cd /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug/src/examples && $(CMAKE_COMMAND) -P CMakeFiles/examplemodule.dir/cmake_clean.cmake
.PHONY : src/examples/CMakeFiles/examplemodule.dir/clean

src/examples/CMakeFiles/examplemodule.dir/depend:
	cd /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lilelr/open-source/bak_mesos-1.3.2 /home/lilelr/open-source/bak_mesos-1.3.2/src/examples /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug/src/examples /home/lilelr/open-source/bak_mesos-1.3.2/cmake-build-debug/src/examples/CMakeFiles/examplemodule.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/examples/CMakeFiles/examplemodule.dir/depend

