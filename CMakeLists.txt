# set a list of items
#set(items_to_buy apple orange pear beer)
## loop over the items
#foreach(item ${items_to_buy})
#  message("Don't forget to buy one ${item}")
#endforeach()

#Check System
if (NOT WIN32)
  cmake_minimum_required(VERSION 2.8.10)
else (NOT WIN32)
  cmake_minimum_required(VERSION 3.7.0)
endif (NOT WIN32)

project(libprocess-start)
#message(${libprocess-start_BINARY_DIR})
#message(${libprocess-start_SOURCE_DIR})
#message(${CMAKE_BINARY_DIR})
#message(${CMAKE_SOURCE_DIR})
#message(${CMAKE_CURRENT_LIST_DIR})

# CMAKE MODULE SETUP.f
#####################
# Paths that are searched when `include(...)` is called.
# 添加include 命令所搜索的路径
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/libprocess/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/stout/cmake)
list(
  APPEND
  CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparty/libprocess/cmake/macros)


#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
#CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
#if(COMPILER_SUPPORTS_CXX11)
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#elseif(COMPILER_SUPPORTS_CXX0X)
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#else()
#  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
#endif()

# Macros.
# ${CMAKE_SOURCE_DIR}/cmake
include(Common)
# ${CMAKE_SOURCE_DIR}/3rdparty/libprocess/cmake/macros
include(External)
# ${CMAKE_SOURCE_DIR}/3rdparty/libprocess/cmake/macros
include(PatchCommand)
# ${CMAKE_SOURCE_DIR}/3rdparty/cmake
include(Versions)
# ${CMAKE_SOURCE_DIR}/3rdparty/cmake
include(cotire)

# Configuration.
# ${CMAKE_SOURCE_DIR}/cmake
include(StartConfigure)
# ${CMAKE_SOURCE_DIR}/cmake
include(CompilationConfigure)
# ${CMAKE_SOURCE_DIR}/3rdparty/libprocess/cmake
include(ProcessConfigure)

#
#message("70" ${PROCESS_LIBS})
#message("71" ${PROCESS_TARGET})
#message("72" ${PROCESS_LIB_DIRS})
#link_directories({PROCESS_LIB_DIRS})
# SUBDIRECTORIES.
#################
#include_directories("/home/lemaker/open-source/libprocess-start/3rdparty/gmock-1.7.0/gtest/include")
#include_directories("/home/lemaker/open-source/libprocess-start/3rdparty/gmock-1.7.0/include")
#
#list(APPEND PROCESS_LIB_DIRS "/home/lemaker/open-source/libprocess-start/3rdparty/glog-0.3.3/.libs")
#
#list(APPEND PROCESS_LIB_DIRS "/home/lemaker/open-source/libprocess-start/3rdparty/gmock-1.7.0/gtest/lib/.libs")
#list(APPEND PROCESS_LIB_DIRS "/home/lemaker/open-source/libprocess-start/3rdparty/gmock-1.7.0/lib/.libs")
#
#link_directories({PROCESS_LIB_DIRS})
add_subdirectory(3rdparty)

add_subdirectory(my_hello)
add_subdirectory(weiguo_server_client)
#add_subdirectory(src)

##future promise
#add_subdirectory(./google/googletest)
#include_directories(./google/googletest/include)
#link_directories(./google/googletest)
#add_excutable(libprocess-start future_promise.cpp)
#set(LIBRARIES test pthread)
#target_link_libraries(future_promise ${LIBRARIES})

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

