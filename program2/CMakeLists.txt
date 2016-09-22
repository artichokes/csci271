cmake_minimum_required(VERSION 3.6)
project(program2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")

set(SOURCE_FILES list.h listNode.h iter.h)
add_executable(program2 ${SOURCE_FILES} test.cpp)
add_executable(program2_test ${SOURCE_FILES} p2main.cpp)
file(COPY ../resources DESTINATION ./)
