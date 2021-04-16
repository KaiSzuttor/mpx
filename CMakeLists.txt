cmake_minimum_required(VERSION 3.14)

project(mpx LANGUAGES CXX VERSION 0.0.1)

find_package(MPI REQUIRED)

add_library(mpx INTERFACE)
target_include_directories(mpx INTERFACE include)
target_compile_features(mpx INTERFACE cxx_std_17)
target_link_libraries(mpx INTERFACE MPI::MPI_CXX)

add_subdirectory(tests)
add_subdirectory(external)
