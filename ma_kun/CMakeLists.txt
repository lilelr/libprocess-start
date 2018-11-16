cmake_minimum_required(VERSION 2.8)

# In this case, this function would:
#
#   (1) compile the `include/mesos/mesos.proto`, which would generate the files
#       `build/include/mesos/mesos.pb.h` and `build/include/mesos/mesos.pb.cc`
#   (2) export the following variables, based on the `BASE_NAME` parameter
#       (a) MESOS_PROTO:    ${MESOS_ROOT}/include/mesos/mesos.proto
#       (b) MESOS_PROTO_CC: ${MESOS_ROOT}/build/include/mesos/mesos.pb.cc
#       (a) MESOS_PROTO_H:   ${MESOS_ROOT}/build/include/mesos/mesos.pb.h
#function(PROTOC_TO_INCLUDE_DIR BASE_NAME BASE_DIR_STRUCTURE)
#
#    set(TO_INCLUDE_DIR
#            -I${MESOS_PUBLIC_INCLUDE_DIR}
#            -I${MESOS_SRC_DIR}
#            --cpp_out=${MESOS_BIN_INCLUDE_DIR})
#
#    # Names of variables we will be publicly exporting.
#    set(PROTO_VAR ${BASE_NAME}_PROTO)    # e.g., MESOS_PROTO
#    set(CC_VAR    ${BASE_NAME}_PROTO_CC) # e.g., MESOS_PROTO_CC
#    set(H_VAR     ${BASE_NAME}_PROTO_H)  # e.g., MESOS_PROTO_H
#
#    # Fully qualified paths for the input .proto files and the output C files.
#    set(PROTO ${MESOS_PUBLIC_INCLUDE_DIR}/${BASE_DIR_STRUCTURE}.proto)
#    set(CC    ${MESOS_BIN_INCLUDE_DIR}/${BASE_DIR_STRUCTURE}.pb.cc)
#    set(H     ${MESOS_BIN_INCLUDE_DIR}/${BASE_DIR_STRUCTURE}.pb.h)
#
#    # Export variables holding the target filenames.
#    set(${PROTO_VAR} ${PROTO} PARENT_SCOPE) # e.g., mesos/mesos.proto
#    set(${CC_VAR}    ${CC}    PARENT_SCOPE) # e.g., mesos/mesos.pb.cc
#    set(${H_VAR}     ${H}     PARENT_SCOPE) # e.g., mesos/mesos.pb.h
#
#    # Compile the .proto file.
#    ADD_CUSTOM_COMMAND(
#            OUTPUT ${CC} ${H}
#            COMMAND ${PROTOC} ${TO_INCLUDE_DIR} ${PROTO}
#            DEPENDS make_bin_include_dir ${PROTO}
#            WORKING_DIRECTORY ${MESOS_BIN})
#endfunction()
#
#PROTOC_TO_INCLUDE_DIR(LELEMASTER                mesos/lelemaster)

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

add_subdirectory(proto)


#message(${PROJECT_BINARY_DIR})
# Define third-party include directories. Tells compiler toolchain where to get
# headers for our third party libs (e.g., -I/path/to/glog on Linux).
###############################################################################
set(MAKUN_INCLUDE_DIRS
        ${MAKUN_INCLUDE_DIRS}
        ${MESOS_PUBLIC_INCLUDE_DIR}
        # Contains (e.g.) compiled *.pb.h files.
        ${PROJECT_BINARY_DIR}/proto/
        ${PROJECT_BINARY_DIR}/ma_kun/proto/
        )
#message("71")
#message(${PROCESS_3RDPARTY_INCLUDE_DIRS})
set(MAKUN_3RDPARTY_INCLUDE_DIRS
        ${MAKUN_3RDPARTY_INCLUDE_DIRS}
        ${PROCESS_INCLUDE_DIRS}
        ${PROCESS_3RDPARTY_INCLUDE_DIRS}
        ${LEVELDB_INCLUDE_DIR}
        )

# Define third-party lib install directories. Used to tell the compiler
# toolchain where to find our third party libs (e.g., -L/path/to/glog on
# Linux).
########################################################################
set(MAKUN_LIB_DIRS
        ${PROCESS_LIB_DIRS}
        )

# Define third-party libs. Used to generate flags that the linker uses to
# include our third-party libs (e.g., -lglog on Linux).
#########################################################################
# 3rdparty/libprocess/cmake/ProcessConfigure.cmake 139 ${Process_libs}
# 49 ${PROCESS_TARGET}
set(MAKUN_LIBS
        ${PROCESS_LIBS}
        ${PROCESS_TARGET}
        )

# INCLUDE DIRECTIVES FOR LELE EXECUTABLE (generates, e.g., -I/path/to/thing
# on Linux).
############################################################################
include_directories(SYSTEM ${MAKUN_3RDPARTY_INCLUDE_DIRS})
include_directories(${MAKUN_INCLUDE_DIRS})

# LINKING LIBRARIES BY DIRECTORY (might generate, e.g., -L/path/to/thing on
# Linux).
###########################################################################
link_directories(${MAKUN_LIB_DIRS})

# THE LELE EXECUTABLE.
#######################

set(MAKUN_HELLO "makun_server")
set(makun_server_SRC server_protobuf.cpp)
add_executable(${MAKUN_HELLO} ${makun_server_SRC})

# ADD LINKER FLAGS (generates, e.g., -lglog on Linux).
######################################################
target_link_libraries(${MAKUN_HELLO} foobar protobuf ${MAKUN_LIBS})

# client_protobuf
set(makun_client_SRC client_protobuf.cpp)
add_executable(makun_client ${makun_client_SRC})
target_link_libraries(makun_client foobar protobuf ${MAKUN_LIBS})

#[[set(lele_http_simple_process_SRC lele_http_simple_process.cpp)
add_executable(lele_http_simple_process ${lele_http_simple_process_SRC})
target_link_libraries(lele_http_simple_process foo ${LELE_LIBS})]]

message(12345)




