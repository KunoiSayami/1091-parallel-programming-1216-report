cmake_minimum_required(VERSION 3.17)
project(1091_parallel_programming_1216_report)


set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP REQUIRED)

add_executable(1091_parallel_programming_1216_report main.cpp)
target_link_libraries(1091_parallel_programming_1216_report OpenMP::OpenMP_CXX)

# add_test(NAME main_test COMMAND "./generate_data.py && $<TARGET_FILE:1091_parallel_programming_1216_report> --file")