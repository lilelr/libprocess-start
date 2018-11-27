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
execute_process(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/3rdparty/gmock-1.7.0
        COMMAND  ./my_make.sh
        )

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

include_directories(${CMAKE_BINARY_DIR}/3rdparty/boost-1.53.0-prefix/src/boost-1.53.0)
include(cmake/protobuf_download.cmake)
include(cmake/protobuf_compile.cmake)

include_directories(${CMAKE_BINARY_DIR}/3rdparty/protobuf_2_6/include)
# protobuf download and function

include_directories(${PROJECT_SOURCE_DIR}/3rdparty/picojson-1.3.0)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/stout/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/libprocess/include)

include_directories(${PROJECT_SOURCE_DIR}/3rdparty/gmock-1.7.0/include)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/gmock-1.7.0/lib/.libs)

include_directories(${PROJECT_SOURCE_DIR}/3rdparty/gmock-1.7.0/gtest/include)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/gmock-1.7.0/gtest/lib/.libs)

include_directories(${CMAKE_BINARY_DIR}/3rdparty/glog-0.3.3/src/glog-0.3.3-lib/lib/include)
link_directories(${CMAKE_BINARY_DIR}/3rdparty/glog-0.3.3/src/glog-0.3.3-lib/lib/lib)
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

# include(weiguo_server_client/cmake/protobuf-2.6.1.cmake)
add_subdirectory(weiguo_server_client)

add_subdirectory(zhangyixin)
add_subdirectory(ma_kun)

#


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

