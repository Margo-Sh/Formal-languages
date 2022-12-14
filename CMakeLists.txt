cmake_minimum_required(VERSION 3.5)

project(Formal_2)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# include(CodeCoverage)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Formal_2 run_test.cpp TestAdd.cpp TestAdd.h Grammar.h Grammar.cpp Chomsky.h Chomsky.cpp CYK.h CYK.cpp )

target_link_libraries(Formal_2 ${GTEST_LIBRARIES} Threads::Threads)

# setup_target_for_coverage(tests 00_start_test coverage)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

