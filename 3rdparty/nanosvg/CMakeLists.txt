cmake_minimum_required(VERSION 3.10)

project(nanosvg)
set(SOURCE_FILES nanosvg.c nanosvg.h nanosvgrast.h)

add_library(nanosvg ${SOURCE_FILES})
