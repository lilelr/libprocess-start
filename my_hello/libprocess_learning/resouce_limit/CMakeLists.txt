add_executable(lele_disk_io_of_a_process limit_disk_io_limit_of_a_process.cpp)

target_link_libraries(lele_disk_io_of_a_process foo ${LELE_LIBS} gmock gtest pthread)


add_executable(lele_limit_cpu limit_cpu.cpp)

target_link_libraries(lele_limit_cpu ${PROCESS_LIBS} ${PROCESS_TARGET} gmock gtest pthread)
