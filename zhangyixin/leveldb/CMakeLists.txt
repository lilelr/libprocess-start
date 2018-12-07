set(LEVELDB_INCLUDE_PATH ${LEVELDB_ROOT}/include)
#set(LEVELDB_LIB ${CMAKE_BINARY_DIR}/3rdparty/leveldb-1.19/src/leveldb-1.19/out-static/libleveldb.a)
#set(level_include /home/zyx/app/leveldb)
include_directories(${LEVELDB_INCLUDE_PATH})
#set(leveldb_lib /home/zyx/app/leveldb/out-static/libleveldb.a)
#message(LEVELDB_LFLAG===  ${LEVELDB_ROOT})

set(yx_leveldb_SRC leveldb.cpp)
add_executable(yx_leveldb ${yx_leveldb_SRC})
target_link_libraries(yx_leveldb ${LEVELDB_LFLAG} pthread)

set(yx_leveldb_01_SRC leveldb_01.cpp)
add_executable(yx_leveldb_01 ${yx_leveldb_01_SRC})
target_link_libraries(yx_leveldb_01 ${LEVELDB_LFLAG} pthread)


