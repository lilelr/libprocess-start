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
PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/ma_kun/protobuf_begin/proto SearchRequest ${CMAKE_BINARY_DIR}/ma_kun libproto_search_result)
include_directories(${SearchRequest_PROTO})
include_directories(${SearchRequest_PROTO_CC})
include_directories(${SearchRequest_PROTO_H})
message(${CMAKE_SOURCE_DIR}777)
message(${CMAKE_BINARY_DIR}888)
message(libproto_search_result)
message(39 ${SearchRequest_PROTO})
message(40 ${SearchRequest_PROTO_CC})
message(41 ${SearchRequest_PROTO_H})

# 自定义下载的protobuf 依赖库和头文件导入结束


set(hwloc_map_SRC hwloc_map.cpp)

message(${hwloc_INCLUDE_DIR})
include_directories(${hwloc_INCLUDE_DIR})

# 生成动态库　shared 表示so, imported 表示从其他地方导入
add_library(libhwloc SHARED IMPORTED)

#Targets can have properties that affect how they are built.
#
#   set_target_properties(target1 target2 ...
#   PROPERTIES prop1 value1
#   prop2 value2 ...)
set_target_properties(libhwloc PROPERTIES IMPORTED_LOCATION ${hwloc_LIB_DIR}/libhwloc.so)

#Make a top-level <target> depend on other top-level targets to ensure that they build before <target> does.
#A top-level target is one created by ADD_EXECUTABLE, ADD_LIBRARY, or ADD_CUSTOM_TARGET.
add_dependencies(libhwloc hwloc)

message(3 ${hwloc_LIB_DIR})

link_directories(${hwloc_LIB_DIR})
set(Hwloc_LIBRARIES hwloc)
#Adds -D define flags to the compilation of source files.



add_executable(hwloc_map ${hwloc_map_SRC})

# 在　cmake/porotobuf_compile.cmake 中，　其中libproto_search_result　是将生成.cc 和　.h 包装成静态库，即　libproto_search_result．a
target_link_libraries(hwloc_map libhwloc ${Protobuf_LIBRARY} libproto_search_result)

## 以下写法都可以：
#target_link_libraries(myProject comm)       # 连接libhello.so库，默认优先链接动态库
#target_link_libraries(myProject libcomm.a)  # 显示指定链接静态库
#target_link_libraries(myProject libcomm.so) # 显示指定链接动态库
#
## 再如：
#target_link_libraries(myProject libcomm.so)　　#这些库名写法都可以。
#target_link_libraries(myProject comm)
#target_link_libraries(myProject -lcomm)
#PROTOC_COMPILE(${CMAKE_SOURCE_DIR}/src/protobuf_begin/proto SearchRequest ${CMAKE_BINARY_DIR}/src)
