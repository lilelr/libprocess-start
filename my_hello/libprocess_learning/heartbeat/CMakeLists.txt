add_executable(lele_heartbeat my_heartbeat.cpp)
target_link_libraries(lele_heartbeat ${LELE_LIBS} gmock gtest pthread)