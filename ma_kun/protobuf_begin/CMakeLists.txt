
#message(${CMAKE_BINARY_DIR})
#include_directories(${CMAKE_BINARY_DIR}/protobuf_begin)
# Find required protobuf package


find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()
message(${Protobuf_INCLUDE_DIRS})
message(${Protobuf_LIBRARIES})

add_subdirectory(proto)

#message(${PROTOBUF_INCLUDE_DIRS})
#include_directories(${PROTOBUF_INCLUDE_DIRS})
#set(PROTOBUF_INCLUDE_DIRS /usr/local/include)
#include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR}/protobuf_begin/proto)
add_executable(Demo1 demo1.cpp)



target_link_libraries(Demo1 ${PROTOBUF_LIBRARIES} foo)

message(${high-level})

set(low-level "low-level")

