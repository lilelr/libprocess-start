#
# 自定义下载的protobuf 依赖库和头文件导入开始
#　${protobuf_2_6_LIB_DIR} 定义在cmake/protobuf_download.cmake 中
set(Protobuf_LIBRARY libprotobuf.so)
link_directories(${protobuf_2_6_LIB_DIR})
message(8 ${Protobuf_LIBRARY} ) # 8libprotobuf.so

## 定义要生成的共享库　imported 表明在别处定义好，导入
#add_library(lele_protobuf_target SHARED IMPORTED)
#
## ${protobuf_2_6_TARGET} 定义在　cmake/protobuf_download.cmake 中
#set_target_properties(lele_protobuf_target PROPERTIES IMPORTED_LOCATION ${protobuf_2_6_TARGET})
#
## 添加　libprotobuf.so
#add_dependencies(lele_protobuf_target protobuf)

# 该函数定义在　cmake/porotobuf_compile.cmake 中，　其中libproto_search_result　是将生成.cc 和　.h 包装成静态库，即　libproto_search_result．a
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/ma_kun/dmi MemInfo ${CMAKE_BINARY_DIR}/ma_kun libproto_meminfo)
include_directories(${CMAKE_BINARY_DIR}/ma_kun)
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/ma_kun/dmi DmiInfo ${CMAKE_BINARY_DIR}/ma_kun libproto_dmiinfo)

include_directories(${SearchRequest_PROTO})
include_directories(${SearchRequest_PROTO_CC})
include_directories(${SearchRequest_PROTO_H})
include_directories(SYSTEM ${MAKUN_3RDPARTY_INCLUDE_DIRS})
include_directories(${MAKUN_INCLUDE_DIRS})
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR})
message(${CMAKE_SOURCE_DIR}777)
message(${CMAKE_BINARY_DIR}888)
message(libproto_search_result)
message(39 ${SearchRequest_PROTO})
message(40 ${SearchRequest_PROTO_CC})
message(41 ${SearchRequest_PROTO_H})

# 自定义下载的protobuf 依赖库和头文件导入结束

set(MAKUN_INCLUDE_DIRS
        ${MAKUN_INCLUDE_DIRS}
        ${MESOS_PUBLIC_INCLUDE_DIR}
        # Contains (e.g.) compiled *.pb.h files.
        ${PROJECT_BINARY_DIR}/proto/
        ${PROJECT_BINARY_DIR}/ma_kun/proto/
        )
#message("71")
#message(${PROCESS_3RDPARTY_INCLUDE_DIRS})
set(MAKUN_3RDPARTY_INCLUDE_DIRS
        ${MAKUN_3RDPARTY_INCLUDE_DIRS}
        ${PROCESS_INCLUDE_DIRS}
        ${PROCESS_3RDPARTY_INCLUDE_DIRS}
        ${LEVELDB_INCLUDE_DIR}
        )

# Define third-party lib install directories. Used to tell the compiler
# toolchain where to find our third party libs (e.g., -L/path/to/glog on
# Linux).
########################################################################
set(MAKUN_LIB_DIRS
        ${PROCESS_LIB_DIRS}
        )

# Define third-party libs. Used to generate flags that the linker uses to
# include our third-party libs (e.g., -lglog on Linux).
#########################################################################
# 3rdparty/libprocess/cmake/ProcessConfigure.cmake 139 ${Process_libs}
# 49 ${PROCESS_TARGET}
set(MAKUN_LIBS
        ${PROCESS_LIBS}
        ${PROCESS_TARGET}
        )

link_directories(${MAKUN_LIB_DIRS})
message(234${MAKUN_LIB_DIRS})

set(dmi_test_SRC dmi_test.cpp)
add_executable(dmi_test ${dmi_test_SRC}
        dmidecode.h dmidecode.cpp
        dmimeminfo.h dmimeminfo.cpp)
target_link_libraries(dmi_test gtest gmock ${MAKUN_LIBS} ${Protobuf_LIBRARY} libproto_dmiinfo libproto_meminfo)

set(dmi_main_SRC dmi_main.cpp)
add_executable(dmi_main ${dmi_main_SRC}
        dmidecode.h dmidecode.cpp
        dmimeminfo.h dmimeminfo.cpp)
target_link_libraries(dmi_main ${MAKUN_LIBS} ${Protobuf_LIBRARY} libproto_dmiinfo libproto_meminfo)

message(${MAKUN_INCLUDE_DIRS})