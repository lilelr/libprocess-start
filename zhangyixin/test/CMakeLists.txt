add_executable(yx_proc_tests proc_tests.cpp)
target_link_libraries(yx_proc_tests foo ${XIN_LIBS} gmock gtest pthread rt glog)