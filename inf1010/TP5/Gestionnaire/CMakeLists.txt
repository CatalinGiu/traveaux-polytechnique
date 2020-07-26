cmake_minimum_required(VERSION 3.3)
project(Gestionnaire)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Gestionnaire.h)
add_executable(Gestionnaire ${SOURCE_FILES})