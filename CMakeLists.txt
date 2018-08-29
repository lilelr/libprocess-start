# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# THE MESOS PROJECT.
####################
if (NOT WIN32)
  cmake_minimum_required(VERSION 2.8.10)
else (NOT WIN32)
  cmake_minimum_required(VERSION 3.7.0)
endif (NOT WIN32)

project(Mesos)
#set(MESOS_MAJOR_VERSION 1)
#set(MESOS_MINOR_VERSION 3)
#set(MESOS_PATCH_VERSION 2)
#set(PACKAGE_VERSION
#  ${MESOS_MAJOR_VERSION}.${MESOS_MINOR_VERSION}.${MESOS_PATCH_VERSION})
#
#set(MESOS_PACKAGE_VERSION ${PACKAGE_VERSION})
#set(MESOS_PACKAGE_SOVERSION 0)


# CMAKE MODULE SETUP.f
#####################
# Paths that are searched when `include(...)` is called.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/libprocess/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/stout/cmake)
list(
  APPEND
  CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/libprocess/cmake/macros)


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Macros.
#include(Common)
include(External)
include(PatchCommand)
include(Versions)
include(VsBuildCommand)
include(cotire)

# Configuration.
include(MesosConfigure)
include(CompilationConfigure)
include(ProcessConfigure)


# SUBDIRECTORIES.
#################
add_subdirectory(3rdparty)
add_subdirectory(my_hello)
#add_subdirectory(src)


# TESTS.
########
#add_custom_target(
#  check ${STOUT_TESTS_TARGET}
#  COMMAND ${PROCESS_TESTS_TARGET}
#  COMMAND ${MESOS_TESTS_TARGET}
#  DEPENDS ${STOUT_TESTS_TARGET} ${PROCESS_TESTS_TARGET} ${MESOS_TESTS_TARGET}
#  )
#
#add_custom_target(
#  tests
#  DEPENDS ${STOUT_TESTS_TARGET} ${PROCESS_TESTS_TARGET} ${MESOS_TESTS_TARGET}
#  )

