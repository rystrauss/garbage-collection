cmake_minimum_required(VERSION 3.15)
project(garbage_collection)

set(CMAKE_CXX_STANDARD 14)

add_library(reference_counting reference_counting.cpp reference_counting.h GCPointer.hpp)