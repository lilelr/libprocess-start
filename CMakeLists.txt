# set a list of items
set(items_to_buy apple orange pear beer)
# loop over the items
foreach(item ${items_to_buy})
  message("Don't forget to buy one ${item}")
endforeach()


if (NOT WIN32)
  cmake_minimum_required(VERSION 2.8.10)
else (NOT WIN32)
  cmake_minimum_required(VERSION 3.7.0)
endif (NOT WIN32)

project(libprocess-start)



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
include(Common)
include(External)
include(PatchCommand)
include(Versions)
#include(VsBuildCommand)
include(cotire)

# Configuration.
include(StartConfigure)
include(CompilationConfigure)
include(ProcessConfigure)


# SUBDIRECTORIES.
#################
add_subdirectory(3rdparty)
add_subdirectory(my_hello)
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

