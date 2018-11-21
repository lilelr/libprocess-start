#CMake处理当前目录
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(WEIGUOW_INCLUDE_DIRS
        ${MESOS_PUBLIC_INCLUDE_DIR}
        ${PROJECT_BINARY_DIR}/weiguo_server_client/proto/
        )

set(WEIGUOW_3RDPARTY_INCLUDE_DIRS
        ${PROCESS_INCLUDE_DIRS}
        ${PROCESS_3RDPARTY_INCLUDE_DIRS}
        ${LEVELDB_INCLUDE_DIR}
        )

set(WEIGUOW_LIB_DIRS
        ${PROCESS_LIB_DIRS}
        )

set(WEIGUOW_LIBS
        ${PROCESS_LIBS}
        ${PROCESS_TARGET})

include_directories(SYSTEM
        ${WEIGUOW_3RDPARTY_INCLUDE_DIRS})

include_directories(${WEIGUOW_INCLUDE_DIRS})

link_directories(${WEIGUOW_LIB_DIRS})

add_subdirectory(StudentManage)
add_subdirectory(proto)


PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/weiguo_server_client/proto Student_pro  ${CMAKE_BINARY_DIR}/weiguo_server_client/proto weiguo_student_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/weiguo_server_client/proto Teacher_pro  ${CMAKE_BINARY_DIR}/weiguo_server_client/proto weiguo_teacher_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/weiguo_server_client/proto Transfile  ${CMAKE_BINARY_DIR}/weiguo_server_client/proto weiguo_transfile_pro)

add_executable(weiguo_student_client student_slave.cpp)
target_link_libraries(weiguo_student_client weiguo_student_pro weiguo_transfile_pro ${WEIGUOW_LIBS})

add_executable(weiguo_teacher_server teacher_master.cpp)
target_link_libraries(weiguo_teacher_server weiguo_student_pro weiguo_teacher_pro weiguo_transfile_pro ${WEIGUOW_LIBS})