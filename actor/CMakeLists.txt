
# Define third-party lib install directories. Used to tell the compiler
# toolchain where to find our third party libs (e.g., -L/path/to/glog on
# Linux).
########################################################################
set(LELE_LIB_DIRS
        ${PROCESS_LIB_DIRS}
        )
link_directories(${LELE_LIB_DIRS})

# Define third-party libs. Used to generate flags that the linker uses to
# include our third-party libs (e.g., -lglog on Linux).
#########################################################################
# 3rdparty/libprocess/cmake/ProcessConfigure.cmake 139 ${Process_libs}
# 49 ${PROCESS_TARGET}
set(LELE_LIBS
        ${PROCESS_LIBS}
        ${PROCESS_TARGET}
        )

set(actor_SRCS myevent.hpp mymessage.hpp actor.hpp actor.cpp actor_main.cpp libevent.hpp libevent.cpp myevent_loop.hpp gate.hpp mygc.hpp actor_reference.hpp)
add_executable(actor_main ${actor_SRCS})
message(3 ${PROCESS_LIBS})
message(4 ${PROCESS_TARGET})
target_link_libraries(actor_main glog gtest event event_core event_pthreads ${LELE_LIBS})