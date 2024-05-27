cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ParallelMergeSort)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable
add_executable(ParallelMergeSort parallel_merge_sort.cpp)

# Find and add pthreads library
find_package(Threads REQUIRED)
target_link_libraries(ParallelMergeSort Threads::Threads)
