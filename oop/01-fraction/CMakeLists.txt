cmake_minimum_required(VERSION 3.29)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(fraction)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

set(GTEST_TIMEOUT 10)

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(main MainFraction.cpp Fraction.cpp)
add_executable(fraction TestFraction.cpp Fraction.cpp)
target_link_libraries(fraction GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(fraction)