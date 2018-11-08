include_directories(${CMAKE_CURRENT_LIST_DIR})

#找到protobuf
set(Protobuf_INCLUDE_DIR "${CMAKE_BINARY_DIR}/3rdparty/protobuf-2.6.1/src/protobuf-2.6.1-lib/lib/include")
find_package(Protobuf REQUIRED)

if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
    message(${PROTOBUF_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "pro tobuf library is needed but cant be found")
endif()

#include_directories(${PROTOBUF_INCLUDE_DIR})

#编译运行proto文件，PROTO_SRCS代表proto.pb.c ; PROTO_HDRS代表proto.tb.h
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS Student_pro.proto Teacher_pro.proto)

add_library(weiguo_foo ${PROTO_SRCS} ${PROTO_HDRS})
#target_include_directories(foo PUBLIC ${Protobuf_INCLUDE_DIRS})
