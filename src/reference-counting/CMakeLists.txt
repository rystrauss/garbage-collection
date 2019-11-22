cmake_minimum_required(VERSION 3.15)
project(reference_counting)

set(SOURCE_FILES reference_counting.h reference_counting.cpp GCPointer.hpp)

add_library(reference_counting SHARED STATIC ${SOURCE_FILES})

install(TARGETS reference_counting DESTINATION ${RC_INSTALL_LIB_DIR})
install(FILES reference_counting.h GCPointer.hpp DESTINATION ${RC_INSTALL_INCLUDE_DIR})