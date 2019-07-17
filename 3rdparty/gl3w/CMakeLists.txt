cmake_minimum_required(VERSION 3.10)

project(gl3w)
set(SOURCE_FILES src/gl3w.c)

add_library(gl3w ${SOURCE_FILES})
target_link_libraries(gl3w dl)
target_include_directories(gl3w PUBLIC include)
