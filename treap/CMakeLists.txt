cmake_minimum_required(VERSION 3.17)
project(Treap)


add_executable(treap test-treap.cpp treap.hpp)

target_link_libraries(
    treap
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(treap)
