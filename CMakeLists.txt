cmake_minimum_required(VERSION 3.17)
project(1091_parallel_programming_1216_report)


set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(GMP REQUIRED)
find_package(OpenMP REQUIRED)

option(DEFINE_FILE_READ "Toggle program should read file from ../data.in (useful in clion)" OFF)

message(STATUS "DEFINE_FILE_READ is ${DEFINE_FILE_READ}")
if(DEFINE_FILE_READ)
    message(STATUS "Compile program with -DREAD_FROM_FILE")
    add_definitions(-DREAD_FROM_FILE)
endif(DEFINE_FILE_READ)

add_executable(1091_parallel_programming_1216_report main.cpp)
target_link_libraries(1091_parallel_programming_1216_report gmp gmpxx OpenMP::OpenMP_CXX)
