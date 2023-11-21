cmake_minimum_required(VERSION 2.8)

project(encrypted_proto_example)

add_executable(server server.c)
add_executable(client client.c)

install(TARGETS server client
        DESTINATION /usr/bin)
