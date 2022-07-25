cmake_minimum_required(VERSION 2.9.0)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fno-exceptions -pedantic -Wall -Wextra -Werror -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code")

project(server C)
add_executable(server server.c)
target_link_libraries(server m)
project(client C)
add_executable(client client.c)
target_link_libraries(client m)

project(echo_server C)
add_executable(echo_server echo_server.c)
target_link_libraries(echo_server m)
project(echo_client C)
add_executable(echo_client echo_client.c)
target_link_libraries(echo_client m)
