cmake_minimum_required(VERSION 3.17)
project(1091_parallel_programming_1216_report)


set(CMAKE_CXX_STANDARD 14)
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake-dependence")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake-dependence")
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake-dependence/FindGMP.cmake")
    message(STATUS "FindGMP.cmake is missing, request file from network")
    set(FIND_GMP_CMAKE_FILE_URL "https://gist.githubusercontent.com/KunoiSayami/82f168e23914f86a8d581ef5719eadda/raw/e5c8ff221cc1ed58d4103873d40b22f6926fc598/FindGMP.cmake")
    set(FIND_GMP_CMAKE_FILE_DOWNLOAD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-dependence/FindGMP.cmake")
    file(DOWNLOAD "${FIND_GMP_CMAKE_FILE_URL}" "${FIND_GMP_CMAKE_FILE_DOWNLOAD_PATH}")
else()
    message(STATUS "Found FindGMP.cmake")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-dependence")

find_package(GMP REQUIRED)
find_package(OpenMP REQUIRED)

option(DEFINE_FILE_READ "Toggle program should read file from ../data.in (useful in clion)" OFF)

message(DEBUG "DEFINE_FILE_READ is ${DEFINE_FILE_READ}")
if(DEFINE_FILE_READ)
    message(STATUS "Compile program with -DREAD_FROM_FILE")
    add_definitions(-DREAD_FROM_FILE)
endif(DEFINE_FILE_READ)

add_executable(1091_parallel_programming_1216_report main.cpp)
target_link_libraries(1091_parallel_programming_1216_report gmp gmpxx OpenMP::OpenMP_CXX)
