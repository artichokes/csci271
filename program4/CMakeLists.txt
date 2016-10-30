cmake_minimum_required(VERSION 3.6)
project(program1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")

set(SOURCE_FILES main.cpp)
add_executable(program4 ${SOURCE_FILES})
file(COPY ../resources DESTINATION ./)
