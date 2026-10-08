cmake_minimum_required(VERSION 3.20)
project(lab01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -g -fsanitize=address -fno-omit-frame-pointer)
add_link_options(-fsanitize=address)

find_package(GTest REQUIRED)
enable_testing()

add_library(lab01_lib src/array_ops.cpp)
target_include_directories(lab01_lib PUBLIC include)

add_executable(lab01_main src/main.cpp)
target_link_libraries(lab01_main PRIVATE lab01_lib)

add_executable(tests test/array_ops_test.cpp)
target_link_libraries(tests PRIVATE lab01_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
