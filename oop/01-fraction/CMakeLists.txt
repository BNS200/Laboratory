project(fraction)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(fraction Fraction.cpp Fraction.h TestFraction.cpp)
target_link_libraries(fraction GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(fraction)

set(GTEST_TIMEOUT 10)