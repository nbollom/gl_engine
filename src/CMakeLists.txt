cmake_minimum_required(VERSION 3.10)

project(engine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    main.cpp
    scene.h
    scene.cpp
        texture_manager.cpp texture_manager.h inlines.h texture.h vertex_manager.cpp vertex_manager.h vertex_array.cpp vertex_array.h shader_program.cpp shader_program.h)

cmake_policy(SET CMP0072 NEW)

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_executable(engine ${SOURCE_FILES})

add_dependencies(engine resources)

target_include_directories(engine PUBLIC ${OPENGL_INCLUDE_DIR} ../3rdparty/gl3w/include/ ../3rdparty/imgui/ ../3rdparty/stb)
target_link_libraries(engine ${OPENGL_gl_LIBRARY} gl3w imgui glfw glm dl)

