set(actor_SRCS myevent.hpp mymessage.hpp actor.hpp actor.cpp actor_main.cpp)
add_executable(actor_main ${actor_SRCS})
target_link_libraries(actor_main glog gtest)