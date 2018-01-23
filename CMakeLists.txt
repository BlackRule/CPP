cmake_minimum_required(VERSION 3.9)
project(CPP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O0")

#add_executable(lab1 lab1.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lab2)
add_executable(lab2 lab2/lab2.cpp)
#add_executable(s s.cpp)
