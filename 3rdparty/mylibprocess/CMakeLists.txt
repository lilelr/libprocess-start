set(lele_TARGET "MyFuture")

message("李乐乐mylibprocess_ 的 PROCESS_LIBS" ${PROCESS_LIBS})

message("李乐乐mylibprocess_ 的 PROCESS_LIB_DIRS" ${PROCESS_LIB_DIRS})

include_directories(SYSTEM ${PROCESS_3RDPARTY_INCLUDE_DIRS})
#include_directories(${PROCESS_INCLUDE_DIRS})

# LINKING LIBRARIES BY DIRECTORY (might generate, e.g., -L/path/to/thing on
# Linux).
###########################################################################
link_directories(${PROCESS_LIB_DIRS})

add_executable(${lele_TARGET} MyFuture.cpp Mylatch.cpp Mylatch.hpp)

message("李乐乐 PROCESS_TARGET" ${PROCESS_TARGET})

target_link_libraries(${lele_TARGET}  ${PROCESS_LIBS} ${PROCESS_TARGET})