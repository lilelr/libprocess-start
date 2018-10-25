add_executable(lele_after_tests after_tests.cpp)
target_link_libraries(lele_after_tests foo ${LELE_LIBS} gmock gtest pthread)