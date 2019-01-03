#CMake处理当前目录
include_directories(${CMAKE_CURRENT_LIST_DIR})

#运行cmake命令的目录,通常是${PROJECT_SOURCE_DIR}/build  (cmake-build-debug)
set(XIN_INCLUDE_DIRS
        ${MESOS_PUBLIC_INCLUDE_DIR}
        ${PROJECT_BINARY_DIR}/yx/proto/
        )
set(XIN_3RDPARTY_INCLUDE_DIRS
        ${PROCESS_INCLUDE_DIRS}
        ${PROCESS_3RDPARTY_INCLUDE_DIRS}
        ${LEVELDB_INCLUDE_DIR}
        )

#PROCESS_LIB_DIRS /home/zyx/project/libprocess-start/cmake-build-debug/3rdparty/glog-0.3.3/src/glog-0.3.3-lib/lib/lib
set(XIN_LIB_DIRS
        ${PROCESS_LIB_DIRS}
        )

# PROCESS_LIBS /usr/lib/x86_64-linux-gnu/libapr-1.socurlglog
# PROCESS_TARGET process-0.0.1
set(XIN_LIBS
        ${PROCESS_LIBS}
        ${PROCESS_TARGET})

include_directories(SYSTEM ${XIN_3RDPARTY_INCLUDE_DIRS})
#[[#工程的顶级目录  CMAKE_BINARY_DIR
include_directories("${CMAKE_BINARY_DIR}/zhangyixin/proto")   #寻找共享库的路径]]

#[[include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()]]


include_directories(${XIN_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR}/zhangyixin/proto)
message(hahahahhahahahahahha   ${CMAKE_BINARY_DIR})
link_directories(${XIN_LIB_DIRS})

add_subdirectory(proto)
#add_subdirectory(test)


PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/zhangyixin/proto Offer  ${CMAKE_BINARY_DIR}/zhangyixin/proto yx_Offer_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/zhangyixin/proto GpuCollection ${CMAKE_BINARY_DIR}/zhangyixin/proto yx_GpuCollection_pro)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/zhangyixin/proto File  ${CMAKE_BINARY_DIR}/zhangyixin/proto yx_File_pro)
include_directories(${CMAKE_BINARY_DIR}/zhangyixin/proto)
#
#
#add_executable(yx_client client_process.cpp)
#target_link_libraries(yx_client yx_Offer_pro yx_File_pro protobuf ${XIN_LIBS})
#
#add_executable(yx_server server_process.cpp)
#target_link_libraries(yx_server yx_Offer_pro yx_File_pro protobuf ${XIN_LIBS})

#[[add_executable(yx_gpu_info gpu_info.cpp)
target_link_libraries(yx_gpu_info yx_Offer_pro yx_GpuInfo_pro protobuf ${XIN_LIBS})

add_executable(yx_gpu_test gpu_test.cpp)
target_link_libraries(yx_gpu_test ${XIN_LIBS})]]

add_subdirectory(gpu_collector)
add_subdirectory(cpu_usage)
add_subdirectory(leveldb)

