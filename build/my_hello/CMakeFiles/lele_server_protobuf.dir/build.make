# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wqn/libprocess-start

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wqn/libprocess-start/build

# Include any dependencies generated for this target.
include my_hello/CMakeFiles/lele_server_protobuf.dir/depend.make

# Include the progress variables for this target.
include my_hello/CMakeFiles/lele_server_protobuf.dir/progress.make

# Include the compile flags for this target's objects.
include my_hello/CMakeFiles/lele_server_protobuf.dir/flags.make

my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o: my_hello/CMakeFiles/lele_server_protobuf.dir/flags.make
my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o: ../my_hello/Lele_server_protobuf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wqn/libprocess-start/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o"
	cd /home/wqn/libprocess-start/build/my_hello && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o -c /home/wqn/libprocess-start/my_hello/Lele_server_protobuf.cpp

my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.i"
	cd /home/wqn/libprocess-start/build/my_hello && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wqn/libprocess-start/my_hello/Lele_server_protobuf.cpp > CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.i

my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.s"
	cd /home/wqn/libprocess-start/build/my_hello && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wqn/libprocess-start/my_hello/Lele_server_protobuf.cpp -o CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.s

my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o.requires:

.PHONY : my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o.requires

my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o.provides: my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o.requires
	$(MAKE) -f my_hello/CMakeFiles/lele_server_protobuf.dir/build.make my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o.provides.build
.PHONY : my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o.provides

my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o.provides.build: my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o


# Object files for target lele_server_protobuf
lele_server_protobuf_OBJECTS = \
"CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o"

# External object files for target lele_server_protobuf
lele_server_protobuf_EXTERNAL_OBJECTS =

my_hello/lele_server_protobuf: my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o
my_hello/lele_server_protobuf: my_hello/CMakeFiles/lele_server_protobuf.dir/build.make
my_hello/lele_server_protobuf: my_hello/proto/libfoo.a
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libapr-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_delta-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_diff-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_subr-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libz.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libapr-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_delta-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_diff-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_subr-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libz.so
my_hello/lele_server_protobuf: 3rdparty/libprocess/src/libprocess-0.0.1.so.0.0.1
my_hello/lele_server_protobuf: /usr/local/lib/libprotobuf.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libapr-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_delta-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_diff-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_subr-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libz.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libapr-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_delta-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_diff-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libsvn_subr-1.so
my_hello/lele_server_protobuf: /usr/lib/x86_64-linux-gnu/libz.so
my_hello/lele_server_protobuf: my_hello/CMakeFiles/lele_server_protobuf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wqn/libprocess-start/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lele_server_protobuf"
	cd /home/wqn/libprocess-start/build/my_hello && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lele_server_protobuf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
my_hello/CMakeFiles/lele_server_protobuf.dir/build: my_hello/lele_server_protobuf

.PHONY : my_hello/CMakeFiles/lele_server_protobuf.dir/build

my_hello/CMakeFiles/lele_server_protobuf.dir/requires: my_hello/CMakeFiles/lele_server_protobuf.dir/Lele_server_protobuf.cpp.o.requires

.PHONY : my_hello/CMakeFiles/lele_server_protobuf.dir/requires

my_hello/CMakeFiles/lele_server_protobuf.dir/clean:
	cd /home/wqn/libprocess-start/build/my_hello && $(CMAKE_COMMAND) -P CMakeFiles/lele_server_protobuf.dir/cmake_clean.cmake
.PHONY : my_hello/CMakeFiles/lele_server_protobuf.dir/clean

my_hello/CMakeFiles/lele_server_protobuf.dir/depend:
	cd /home/wqn/libprocess-start/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wqn/libprocess-start /home/wqn/libprocess-start/my_hello /home/wqn/libprocess-start/build /home/wqn/libprocess-start/build/my_hello /home/wqn/libprocess-start/build/my_hello/CMakeFiles/lele_server_protobuf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : my_hello/CMakeFiles/lele_server_protobuf.dir/depend
