cmake_minimum_required(VERSION 3.6)
project(program6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")

add_executable(program6_dfs dfs.cpp)
add_executable(program6_kahn khan.cpp)
file(COPY ../resources DESTINATION ./)
