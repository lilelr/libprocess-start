add_executable(lele_disk_io_of_a_process limit_disk_io_limit_of_a_process.cpp)

target_link_libraries(lele_disk_io_of_a_process foo ${LELE_LIBS} gmock gtest pthread)
