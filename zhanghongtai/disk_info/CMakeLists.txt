add_subdirectory(proto)
message(2:\n ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#heldon_lsblk
add_executable(heldon_lsblk lsblk.cpp )
target_link_libraries(heldon_lsblk ${LELE_LIBS} disk_info)

add_executable(heldon_statfs statfs.cpp)
target_link_libraries(heldon_statfs ${LELE_LIBS})