cmake_minimum_required(VERSION 3.17)
project(1091_parallel_programming_1216_report)


set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP REQUIRED)

if (NOT WIN32)
    add_compile_options(-Wall -Wextra)
endif()

add_executable(1091_parallel_programming_1216_report main.cpp)
target_link_libraries(1091_parallel_programming_1216_report OpenMP::OpenMP_CXX)

add_executable(ompmatrix ompmatrix.cpp)
target_link_libraries(ompmatrix OpenMP::OpenMP_CXX)

find_package(CUDA)
if(CUDA_FOUND)
    project(cuda_test CUDA)
    message(STATUS "Found cuda")
    set(CMAKE_CUDA_STANDARD 14)

    add_executable(cuda_test cuda.cu)

    set_target_properties(
            cuda_test
            PROPERTIES
            CUDA_SEPARABLE_COMPILATION ON)
endif()