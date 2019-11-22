cmake_minimum_required(VERSION 3.15)
project(garbge-collection)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(RC_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(RC_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RC_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(RC_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/reference-counting)

include_directories(${RC_INSTALL_INCLUDE_DIR})
include_directories(${RC_HEADERS_DIR})

add_subdirectory(src)