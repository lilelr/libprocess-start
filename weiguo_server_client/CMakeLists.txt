#CMake处理当前目录
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories("${CMAKE_BINARY_DIR}/weiguo_server_client/proto")

add_subdirectory(proto)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(WEIGUOW_INCLUDE_DIRS
        ${MESOS_PUBLIC_INCLUDE_DIR}
        ${PROJECT_BINARY_DIR}/Server_Client/proto/
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

#use protobuf 2.6 to generate the relevant headers and cpps
# 该函数定义在　cmake/porotobuf_compile.cmake 中，　其中foo　是将生成.cc 和　.h 包装成静态库，即　libfoo.a
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/weiguo_server_client/proto Student_pro  ${CMAKE_BINARY_DIR}/weiguo_server_client/proto weiguo_student_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/weiguo_server_client/proto Teacher_pro  ${CMAKE_BINARY_DIR}/weiguo_server_client/proto weiguo_teacher_pro)
link_directories(${CMAKE_BINARY_DIR}/weiguo_server_client/)

add_executable(weiguo_student_client student_slave.cpp)
target_link_libraries(weiguo_student_client weiguo_student_pro ${WEIGUOW_LIBS})

add_executable(weiguo_teacher_server teacher_master.cpp)
target_link_libraries(weiguo_teacher_server weiguo_student_pro weiguo_teacher_pro ${WEIGUOW_LIBS})