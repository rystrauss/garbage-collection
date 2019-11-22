cmake_minimum_required(VERSION 3.15)
project(gcpointer_example)

add_subdirectory(reference-counting)

set(SOURCE_FILES gcpointer_example.cpp)

add_executable(gcpointer_example ${SOURCE_FILES})
target_link_libraries(gcpointer_example reference_counting)
install(TARGETS gcpointer_example DESTINATION ${RC_INSTALL_BIN_DIR})