# teacher_protobuf
set(teacher_protobuf_SRC teacher_protobuf.cpp)
add_executable(lele_teacher_protobuf ${teacher_protobuf_SRC})
target_link_libraries(lele_teacher_protobuf foo protobuf ${LELE_LIBS})

# student_protobuf
set(student_protobuf_SRC student_protobuf.cpp)
add_executable(lele_student_protobuf ${student_protobuf_SRC})
target_link_libraries(lele_student_protobuf foo protobuf ${LELE_LIBS})