cmake_minimum_required(VERSION 3.11)
project(tp2)

set(CMAKE_CXX_STANDARD 14)

add_executable(glouton src/glouton.cpp src/shared.h src/shared.cpp src/glouton.h src/main_glouton.cpp)
add_executable(progdyn src/shared.h src/shared.cpp src/progdyn.cpp src/progdyn.h)
add_executable(local src/shared.h src/shared.cpp src/local.cpp src/local.h src/glouton.h src/glouton.cpp)
