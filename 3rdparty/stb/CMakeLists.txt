cmake_minimum_required(VERSION 3.10)

project(stb)
set(SOURCE_FILES stb_image.c stb_image.h)

add_library(stb ${SOURCE_FILES})
