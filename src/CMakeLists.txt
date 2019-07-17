cmake_minimum_required(VERSION 3.10)

project(gl_engine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        scene.h
        scene.cpp
        texture_manager.cpp
        texture_manager.h
        inlines.h
        texture.h
        vertex_manager.cpp
        vertex_manager.h
        vertex_array.cpp
        vertex_array.h
        shader_program.cpp
        shader_program.h
        sprite.cpp
        sprite.h)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_library(gl_engine ${SOURCE_FILES})

target_include_directories(gl_engine PUBLIC ${OPENGL_INCLUDE_DIR} ../3rdparty/gl3w/include/ ../3rdparty/imgui/ ../3rdparty/stb ../3rdparty/nanosvg)
target_link_libraries(gl_engine ${OPENGL_gl_LIBRARY} gl3w imgui glfw glm stb nanosvg)

project(gl_engine_test)
add_executable(gl_engine_test main.cpp)
add_dependencies(gl_engine_test resources)
target_link_libraries(gl_engine_test gl_engine)

