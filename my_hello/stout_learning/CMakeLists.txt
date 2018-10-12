
message("lele")
message(${PROCESS_LIBS}+"\n")
message("${LELE_LIBS}")

include_directories("/home/lilelr/open-source/libprocess-start/3rdparty/stout/include")
set(lele_stout_my_learning_SRC lele_stout_my_learning.cpp)
add_executable(lele_stout_my_learning_main ${lele_stout_my_learning_SRC})
target_link_libraries(lele_stout_my_learning_main  gmock gtest pthread)


set(lele_option_usage_SRC lele_option_usage.cpp)
add_executable(lele_option_usage_main ${lele_option_usage_SRC})
target_link_libraries(lele_option_usage_main  gmock gtest pthread)