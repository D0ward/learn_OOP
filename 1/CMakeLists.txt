cmake_minimum_required(VERSION 3.16)

project(lab1)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(input input_lib/input.hpp input_lib/input.cpp)
add_library(lib lib.hpp lib.cpp)

#target_link_libraries(prog input lib)
link_libraries(input lib)

add_executable(prog prog.cpp)
