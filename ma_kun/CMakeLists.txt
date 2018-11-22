

#add_subdirectory(proto)
#add_subdirectory(hwloc_example)
add_subdirectory(dmi)

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
#
#set(MAKUN_HELLO "makun_server")
#set(makun_server_SRC server_protobuf.cpp)
#add_executable(${MAKUN_HELLO} ${makun_server_SRC})
#
## ADD LINKER FLAGS (generates, e.g., -lglog on Linux).
#######################################################
#target_link_libraries(${MAKUN_HELLO} foobar protobuf ${MAKUN_LIBS})
#
## client_protobuf
#set(makun_client_SRC client_protobuf.cpp)
#add_executable(makun_client ${makun_client_SRC})
#target_link_libraries(makun_client foobar protobuf ${MAKUN_LIBS})
#
##[[set(dmi_test_SRC dmi/dmi_test.cpp)
#add_executable(dmi_test ${dmi_test_SRC}
#        dmi/dmidecode.h dmi/dmidecode.cpp)
#target_link_libraries(dmi_test foobar protobuf ${MAKUN_LIBS})]]
#message(12345)




