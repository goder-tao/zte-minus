cmake_minimum_required(VERSION 3.19)
project(zte)

set(CMAKE_CXX_STANDARD 11)

add_executable(zte head-file/hash.cpp  main9.cpp)
add_subdirectory(zte-main)
add_subdirectory(test)

#SET(CMAKE_CXX_COMPILER "clang++")
