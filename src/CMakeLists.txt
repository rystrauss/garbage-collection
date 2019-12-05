cmake_minimum_required(VERSION 3.15)

add_subdirectory(gcpointer)

set(SOURCE_FILES gcpointer_example.cpp)

add_executable(gcpointer_example ${SOURCE_FILES})
target_link_libraries(gcpointer_example gcpointer)
install(TARGETS gcpointer_example DESTINATION ${RC_INSTALL_BIN_DIR})