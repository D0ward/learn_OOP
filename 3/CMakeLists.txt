cmake_minimum_required(VERSION 3.16)

project(lab3)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_compile_options(--coverage)
add_link_options(--coverage)

add_subdirectory(security_system)

#add_subdirectory(test)

add_executable(prog prog.cpp)

target_link_libraries(prog security_system)

add_executable(test_multithread test.cpp)
target_link_libraries(test_multithread security_system)
