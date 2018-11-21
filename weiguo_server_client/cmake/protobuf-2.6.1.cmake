include(ExternalProject)

set(PROTOBUF_ROOT_WEIGUO            ${CMAKE_BINARY_DIR}/weiguo_server_client/thirdparty/protobuf_weiguo)
set(PROTOBUF_LIB_DIR_WEIGUO         ${PROTOBUF_ROOT_WEIGUO}/lib)
set(PROTIBUF_INCLUDE_DIR_WEIGUO     ${PROTOBUF_ROOT_WEIGUO}/include)

set(PROTOBUF_URL_WEIGUO             https://github.com/weiguow/protobuf-2.6.1/archive/master.zip)
set(PROTOBUF_CONFIGURE_WEIGUO       cd ${PROTOBUF_ROOT_WEIGUO}/src/protobuf_weiguo && ./autogen.sh && ./configure --prefix=${PROTOBUF_ROOT_WEIGUO})
set(PROTOBUF_MAKE_WEIGUO            cd ${PROTOBUF_ROOT_WEIGUO}/src/protobuf_weiguo && make)
set(PROTOBUF_INSTALL_WEIGUO         cd ${PROTOBUF_ROOT_WEIGUO}/src/protobuf_weiguo && make install)
set(PROTOBUF_COMPILER_WEIGUO        ${PROTOBUF_ROOT_WEIGUO}/bin/protoc)

ExternalProject_Add(protobuf_weiguo
        URL                  ${PROTOBUF_URL_WEIGUO}
        DOWNLOAD_NAME        protobuf-2.6.1.zip
        PREFIX               ${PROTOBUF_ROOT_WEIGUO}
        CONFIGURE_COMMAND    ${PROTOBUF_CONFIGURE_WEIGUO}
        BUILD_COMMAND        ${PROTOBUF_MAKE_WEIGUO}
        INSTALL_COMMAND      ${PROTOBUF_INSTALL_WEIGUO}
)





