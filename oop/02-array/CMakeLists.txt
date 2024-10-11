# CMake 3.27+ for C++23 experimental features and CMake 3.30+ for C++26
cmake_minimum_required(VERSION 3.27..3.30 FATAL_ERROR)
message(STATUS "CMake ${CMAKE_VERSION}")

# Force to run cmake from the project root
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Run cmake from the project root: cmake -B build -S . -G Ninja")
endif()

# Choose C/C++23
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "clang")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable C++ modules 'import std' feature and choose vcpkg clang++ toolchain
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# Project setup
project(array VERSION 0.0.1 LANGUAGES C CXX)

# Add base interfaces for the project
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_23 c_std_23)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options (project_options INTERFACE -fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_compile_options (project_options INTERFACE -fcolor-diagnostics)
endif()

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings
  INTERFACE
  -Wall
  -Wextra
  -Wshadow
  -Wbuiltin-macro-redefined
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Wnull-dereference
  -Wdouble-promotion
  -Wformat=2
  -pedantic
)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(project_warnings INTERFACE
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wlogical-op
    -Wuseless-cast
  )
endif()

# Cmake options
option(ENABLE_CXX20_MODULES "Enable C++20 modules" OFF)
option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" ON)
option(ENABLE_ASAN "Enable address sanitizer" ON)

option(ENABLE_CPPCHECK "Enable cppcheck" ON)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
option(ENABLE_CCACHE "Enable ccache" ON)

option(ENABLE_GTEST "Enable unit tests" ON)
option(ENABLE_XTENSOR "Enable xtensor" OFF)
option(ENABLE_CBLAS "Enable cblas" OFF)
option(ENABLE_EIGEN3 "Enable eigen3" OFF)
option(ENABLE_NUMCPP "Enable numcpp" OFF)
option(ENABLE_MKL "Enable Intel MKL" OFF)
option(ENABLE_TBB "Enable Intel TBB" OFF)
option(ENABLE_PTHREADS "Enable Intel pthreads" OFF)

# Toggle C++20 modules
if(ENABLE_CXX20_MODULES)
  set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
  set(CMake_TEST_CXXModules_UUID "a246741c-d067-4019-a8fb-3d16b0c9d1d3")

  set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "clang")

  set(CMAKE_CXX_SCAN_FOR_MODULES ON)
  set(CMAKE_CXX_MODULE_STD 1)
endif()

# Toggle code coverage
if(ENABLE_COVERAGE)
  target_compile_options(project_options INTERFACE --coverage -O0 -g)
  target_link_libraries(project_options INTERFACE --coverage)
endif()

# Toggle sanitizers
if(ENABLE_ASAN)
  target_compile_options(project_options INTERFACE -fsanitize=address)
  target_link_libraries(project_options INTERFACE -fsanitize=address)
endif()

# Toggle C/C++ static analyzer
if(ENABLE_CPPCHECK)
  find_program(CPPCHECK_PROGRAM NAMES cppcheck REQUIRED)
  if (CPPCHECK_PROGRAM)
    set(cppcheck_platform --platform=unix64 --template=clang)
    set(cppcheck_opts --enable=all --inline-suppr --quiet --suppressions-list=${PROJECT_SOURCE_DIR}/.cppcheck.supp)
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK_PROGRAM} --std=c++${CMAKE_CXX_STANDARD} ${cppcheck_platform} ${cppcheck_opts})
  else()
    message(WARNING "Could not find cppcheck, skipping!")
  endif()
endif()

# Toggle C/C++ clang-based static analyzer and linter
if(ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_PROGRAM NAMES clang-tidy REQUIRED)
  if (CLANG_TIDY_PROGRAM)
    set(clang_tidy_extra -extra-arg=-fprebuilt-module-path=${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}lib.dir)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_PROGRAM} ${clang_tidy_extra} --use-color)
  else()
    message(WARNING "Could not find ckang-tidy, skipping!")
  endif()
endif()

# Toggle compiler cache
if(ENABLE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    set(ccacheEnv CCACHE_BASEDIR=${CMAKE_BINARY_DIR} CCACHE_CPP2=true CCACHE_SLOPPINESS=pch_defines,time_macros,include_file_ctime)
    set(CMAKE_C_COMPILER_LAUNCHER ${CMAKE_COMMAND} -E env ${ccacheEnv} ${CCACHE_PROGRAM} PARENT_SCOPE)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CMAKE_COMMAND} -E env ${ccacheEnv} ${CCACHE_PROGRAM} PARENT_SCOPE)
  else ()
    message(WARNING "Could not find ccache, skipping!")
  endif ()
endif()

# Add targets
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE source/array.cpp source/array.h)
target_link_libraries(${PROJECT_NAME} PRIVATE project_options project_warnings)

if(ENABLE_CXX20_MODULES)
  add_library(${PROJECT_NAME}lib)
  target_sources(${PROJECT_NAME}lib PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES source/module.cxx)
  target_link_libraries(${PROJECT_NAME}lib PRIVATE project_options project_warnings)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}lib)
  target_compile_definitions(${PROJECT_NAME} PUBLIC USE_CXX20_MODULES)
endif()

# Toggle GoogleTest unit tests
if(ENABLE_GTEST)
  enable_testing()
  find_package(GTest CONFIG REQUIRED)
  
  add_executable(${PROJECT_NAME}_test)
  target_sources(${PROJECT_NAME}_test PRIVATE tests/testArray.cpp)
  #target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
  target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest_main)
  target_link_libraries(${PROJECT_NAME}_test PRIVATE project_options project_warnings)

  if(ENABLE_CXX20_MODULES)
    target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME}lib)
    target_compile_definitions(${PROJECT_NAME}_test PUBLIC USE_CXX20_MODULES)
  endif()

  set(GTEST_TIMEOUT 10)

  include(CTest)
  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME})
endif()

# Toggle Xtensor
if(ENABLE_XTENSOR)
  find_package(xtensor CONFIG REQUIRED)
  find_package(xtensor-io CONFIG REQUIRED)
  find_package(xtensor-blas CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE xtensor::use_TBB xtensor::optimize xtensor::use_xsimd)
  target_link_libraries(${PROJECT_NAME} PRIVATE xtensor-io xtensor-blas)
endif()

# Toggle GNU pthreads
if(ENABLE_PTHREADS)
  find_package(pthread CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

# Toggle NumCpp
if(ENABLE_NUMCPP)
  find_package(NumCpp CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE NumCpp::NumCpp)
endif()

# Toggle BLAS
if(ENABLE_CBLAS)
  find_package(cBLAS CONFIG REQUIRED)
  find_package(clBLAS CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE cBLAS::cBLAS)
  target_link_libraries(${PROJECT_NAME} PRIVATE clBLAS::clBLAS)
endif()

# Toggle Eigen3
if(ENABLE_EIGEN3)
  find_package(Eigen3 CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen3)
endif()

# Toggle Intel TBB
if(ENABLE_TBB)
  find_package(TBB CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE TBB::tbb TBB::tbbmalloc)
endif()

# Toggle Intel MKL
if(ENABLE_MKL)
  find_package(MKL CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE MKL::MKL)
endif()

if(ENABLE_CXX20_MODULES)
  install(TARGETS ${PROJECT_NAME}lib ARCHIVE PUBLIC_HEADER FILE_SET cxx_modules DESTINATION include CXX_MODULES_BMI DESTINATION share/cxx-modules)
  include(CPack)
endif()
