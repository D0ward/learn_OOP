
find_package(Catch2 REQUIRED)

add_executable(testing testing.cpp)

target_link_libraries(testing triple_signal triple_vector Catch2::Catch2WithMain)
