cmake_minimum_required(VERSION 3.6)
project(program3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")

set(SOURCE_FILES BST.h)
add_executable(program3 ${SOURCE_FILES} main.cpp)
file(COPY ../resources DESTINATION ./)
