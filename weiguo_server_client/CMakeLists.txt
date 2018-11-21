#CMake处理当前目录
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(WEIGUOW_LIB_DIRS ${PROCESS_LIB_DIRS})
link_directories(${WEIGUOW_LIB_DIRS})

set(WEIGUOW_LIBS ${PROCESS_LIBS} ${PROCESS_TARGET})

add_subdirectory(StudentManage)
add_subdirectory(proto)

include(cmake/protobuf-2.6.1-compile.cmake)

PROTOC_COMPILE_WEIGUO(${CMAKE_SOURCE_DIR}/weiguo_server_client/proto Student_pro  ${CMAKE_BINARY_DIR}/weiguo_server_client/proto weiguo_student_pro)
PROTOC_COMPILE_WEIGUO(${CMAKE_SOURCE_DIR}/weiguo_server_client/proto Teacher_pro  ${CMAKE_BINARY_DIR}/weiguo_server_client/proto weiguo_teacher_pro)
PROTOC_COMPILE_WEIGUO(${CMAKE_SOURCE_DIR}/weiguo_server_client/proto Transfile    ${CMAKE_BINARY_DIR}/weiguo_server_client/proto weiguo_transfile_pro)

add_executable(weiguo_student_client student_slave.cpp)
target_link_libraries(weiguo_student_client weiguo_student_pro weiguo_transfile_pro ${WEIGUOW_LIBS})

add_executable(weiguo_teacher_server teacher_master.cpp)
target_link_libraries(weiguo_teacher_server weiguo_student_pro weiguo_teacher_pro weiguo_transfile_pro ${WEIGUOW_LIBS})