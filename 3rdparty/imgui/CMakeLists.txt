cmake_minimum_required(VERSION 3.10)

project(imgui)
set(SOURCE_FILES imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_impl_glfw.cpp imgui_impl_opengl3.cpp imgui_widgets.cpp)

add_library(imgui ${SOURCE_FILES})
target_include_directories(imgui PUBLIC ../gl3w/include)