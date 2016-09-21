cmake_minimum_required(VERSION 3.6)
project(program2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")

set(SOURCE_FILES main.cpp list.h listNode.h iter.h)
add_executable(program2 ${SOURCE_FILES})
file(COPY ../resources DESTINATION ./)
