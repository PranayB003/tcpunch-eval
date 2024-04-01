cmake_minimum_required(VERSION 3.10)
project(tcpunch-eval)

add_executable(node-a node-a.cpp)
add_executable(node-b node-b.cpp)

target_include_directories(node-a PRIVATE ${CMAKE_SOURCE_DIR}/extern/tcpunch/client)
target_include_directories(node-b PRIVATE ${CMAKE_SOURCE_DIR}/extern/tcpunch/client)

target_link_libraries(node-a ${CMAKE_SOURCE_DIR}/extern/tcpunch/client/build/libtcpunch.a)
target_link_libraries(node-b ${CMAKE_SOURCE_DIR}/extern/tcpunch/client/build/libtcpunch.a)
