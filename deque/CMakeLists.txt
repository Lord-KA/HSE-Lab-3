cmake_minimum_required(VERSION 3.17)
project(Deque)


add_executable(deque test-deque.cpp deque.hpp)

target_link_libraries(
    deque
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(deque)
