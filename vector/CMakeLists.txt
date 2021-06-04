cmake_minimum_required(VERSION 3.14)

project(Vector)


add_executable(vector test-vector.cpp vector.hpp)

target_link_libraries(
    vector
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(vector)
