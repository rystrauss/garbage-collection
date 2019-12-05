cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES reference_counting.h reference_counting.cpp GCPointer.hpp)

add_library(gcpointer SHARED STATIC ${SOURCE_FILES})

install(TARGETS gcpointer DESTINATION ${RC_INSTALL_LIB_DIR})
install(FILES GCPointer.hpp DESTINATION ${RC_INSTALL_INCLUDE_DIR})