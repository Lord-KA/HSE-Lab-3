cmake_minimum_required(VERSION 3.17)
project(linkedList)


add_executable(linkedList test-linkedlist.cpp linkedlist.hpp)

target_link_libraries(
    linkedList
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(linkedList)
