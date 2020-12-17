cmake_minimum_required(VERSION 3.17)
project(1091_parallel_programming_1216_report)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(GMP REQUIRED)
add_executable(1091_parallel_programming_1216_report main.cpp)
target_link_libraries(1091_parallel_programming_1216_report gmp gmpxx)

add_executable(miller_rabin_test miller_rabin.cpp)
target_link_libraries(miller_rabin_test gmp gmpxx)