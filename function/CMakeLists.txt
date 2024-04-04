cmake_minimum_required(VERSION 3.20)
project(cloud_run_func CXX)

find_package(functions_framework_cpp REQUIRED)
find_package(Threads)

add_executable(cloud_run_func cloud_run_func.cpp)
target_compile_features(cloud_run_func PRIVATE cxx_std_17)
target_include_directories(cloud_run_func PRIVATE ${CMAKE_SOURCE_DIR}/extern/tcpunch/client)
target_link_libraries(cloud_run_func ${CMAKE_SOURCE_DIR}/extern/tcpunch/client/build/libtcpunch.a)
target_link_libraries(cloud_run_func functions-framework-cpp::framework)

include(GNUInstallDirs)
install(TARGETS cloud_run_func RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
