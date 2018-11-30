#message(${PROJECT_BINARY_DIR})
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
# 3rdparty/libprocess/cmake/ProcessConfigure.cmake 139 ${Process_libs}
# 49 ${PROCESS_TARGET}
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

# THE EXECUTABLE.
#######################
add_subdirectory(disk_info)


