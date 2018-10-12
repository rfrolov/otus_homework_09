cmake_minimum_required(VERSION 3.6)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(TestConcepts TestConcepts.cpp Concepts.h)

set_target_properties(
        TestConcepts PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)