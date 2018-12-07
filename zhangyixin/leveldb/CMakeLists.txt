set(level_include /home/zyx/app/leveldb)
include_directories(${level_include})
set(leveldb_lib /home/zyx/app/leveldb/out-static/libleveldb.a)

set(yx_leveldb_SRC leveldb.cpp)
add_executable(yx_leveldb ${yx_leveldb_SRC})
target_link_libraries(yx_leveldb ${leveldb_lib} pthread)

set(yx_leveldb_01_SRC leveldb_01.cpp)
add_executable(yx_leveldb_01 ${yx_leveldb_01_SRC})
target_link_libraries(yx_leveldb_01 ${leveldb_lib} pthread)