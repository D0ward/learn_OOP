cmake_minimum_required(VERSION 3.16)

project(lab2_ex)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_compile_options(--coverage)
add_link_options(--coverage)

add_subdirectory(input)

add_subdirectory(lib)
#add_subdirectory(simple_class)

add_executable(prog prog.cpp)

target_link_libraries(prog complex_class simple_class input)
