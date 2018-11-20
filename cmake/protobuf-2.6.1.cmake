include(ExternalProject)

set(PROTOBUF_ROOT_z            ${CMAKE_BINARY_DIR}/thirdparty/protobuf-2.6.1.1)
set(PROTOBUF_LIB_DIR         ${PROTOBUF_ROOT_z}/lib)
set(PROTIBUF_INCLUDE_DIR     ${PROTOBUF_ROOT_z}/include)

set(PROTOBUF_URL             https://github.com/weiguow/protobuf-2.6.1/archive/master.zip)
set(PROTOBUF_CONFIGURE       cd ${PROTOBUF_ROOT_z}/src/protobuf-2.6.1.1 && ./configure --prefix=${PROTOBUF_ROOT_z})
set(PROTOBUF_MAKE            cd ${PROTOBUF_ROOT_z}/src/protobuf-2.6.1.1 && make)
set(PROTOBUF_INSTALL         cd ${PROTOBUF_ROOT_z}/src/protobuf-2.6.1.1 && make install)
set(PROTOBUF_COMPILER        ${PROTOBUF_ROOT_z}/bin/protoc)

ExternalProject_Add(protobuf-2.6.1.1
        URL                  ${PROTOBUF_URL}
        DOWNLOAD_NAME        protobuf-2.6.1.1.zip
        PREFIX               ${PROTOBUF_ROOT_z}
        CONFIGURE_COMMAND    ${PROTOBUF_CONFIGURE}
        BUILD_COMMAND        ${PROTOBUF_MAKE}
        INSTALL_COMMAND      ${PROTOBUF_INSTALL}
)




