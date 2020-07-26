cmake_minimum_required(VERSION 3.12)
project(tp1)

set(CMAKE_CXX_STANDARD 14)

add_executable(counting src/counting.cpp src/utilityFunctions.h src/utilityFunctions.cpp src/counting.h)
add_executable(quick src/quick.cpp src/utilityFunctions.h src/utilityFunctions.cpp src/quick.h)
