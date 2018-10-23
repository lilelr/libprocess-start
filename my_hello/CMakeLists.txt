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
add_subdirectory(stout_learning)
add_subdirectory(weiguo_stout_learning)

set(LELE_HELLO "lele_server_protobuf")
set(lele_hello_SRC Lele_server_protobuf.cpp)

message(${PROJECT_BINARY_DIR})
# Define third-party include directories. Tells compiler toolchain where to get
# headers for our third party libs (e.g., -I/path/to/glog on Linux).
###############################################################################
set(LELE_INCLUDE_DIRS
        ${LELE_INCLUDE_DIRS}
        ${MESOS_PUBLIC_INCLUDE_DIR}
        # Contains (e.g.) compiled *.pb.h files.
        ${PROJECT_BINARY_DIR}/proto/
        ${PROJECT_BINARY_DIR}/my_hello/proto/
        )
message("71")
message(${PROCESS_3RDPARTY_INCLUDE_DIRS})
set(LELE_3RDPARTY_INCLUDE_DIRS
        ${LELE_3RDPARTY_INCLUDE_DIRS}
        ${PROCESS_INCLUDE_DIRS}
        ${PROCESS_3RDPARTY_INCLUDE_DIRS}
        ${LEVELDB_INCLUDE_DIR}
        )

# Define third-party lib install directories. Used to tell the compiler
# toolchain where to find our third party libs (e.g., -L/path/to/glog on
# Linux).
########################################################################
set(LELE_LIB_DIRS
        ${PROCESS_LIB_DIRS}
        )

# Define third-party libs. Used to generate flags that the linker uses to
# include our third-party libs (e.g., -lglog on Linux).
#########################################################################
set(LELE_LIBS
        ${PROCESS_LIBS}
        ${PROCESS_TARGET}
        )

# INCLUDE DIRECTIVES FOR LELE EXECUTABLE (generates, e.g., -I/path/to/thing
# on Linux).
############################################################################
include_directories(SYSTEM ${LELE_3RDPARTY_INCLUDE_DIRS})
include_directories(${LELE_INCLUDE_DIRS})

# LINKING LIBRARIES BY DIRECTORY (might generate, e.g., -L/path/to/thing on
# Linux).
###########################################################################
link_directories(${LELE_LIB_DIRS})

# THE LELE EXECUTABLE.
#######################
add_executable(${LELE_HELLO} ${lele_hello_SRC})

# ADD LINKER FLAGS (generates, e.g., -lglog on Linux).
######################################################
target_link_libraries(${LELE_HELLO} foo protobuf ${LELE_LIBS})

set(client_server_message_event_SRC client_server_message_event.cpp)
add_executable(client_server_message_event ${client_server_message_event_SRC})
target_link_libraries(client_server_message_event foo protobuf ${LELE_LIBS})

# client_protobuf
set(client_protobuf_SRC client_protobuf.cpp)
add_executable(client_protobuf ${client_protobuf_SRC})
target_link_libraries(client_protobuf foo protobuf ${LELE_LIBS})

# test_master
set(test_master_SRC test-master.cpp)
add_executable(test-master ${test_master_SRC})
target_link_libraries(test-master foo protobuf ${LELE_LIBS})

# test_slave
set(test-slave_SRC test-slave.cpp)
add_executable(test-slave ${test-slave_SRC})
target_link_libraries(test-slave foo protobuf ${LELE_LIBS})

# future promise
set(future_promise_SRC future_promise.cpp)
add_executable(future_promise ${future_promise_SRC})
target_link_libraries(future_promise foo protobuf ${LELE_LIBS} pthread gmock gtest)

#
set(http_process_learning_SRC http_process_learning.cpp)
add_executable(http_process_learning ${http_process_learning_SRC})
target_link_libraries(http_process_learning foo ${LELE_LIBS})


set(simpleserver_SRC simpleserver.cpp)
add_executable(simpleserver ${simpleserver_SRC})
target_link_libraries(simpleserver foo ${LELE_LIBS})


set(lele_http_simple_process_SRC lele_http_simple_process.cpp)
add_executable(lele_http_simple_process ${lele_http_simple_process_SRC})
target_link_libraries(lele_http_simple_process foo ${LELE_LIBS})

message(${CMAKE_CURRENT_LIST_DIR})

