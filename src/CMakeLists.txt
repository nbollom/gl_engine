cmake_minimum_required(VERSION 3.10)

project(engine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
#find_package(PNG REQUIRED)
#find_package(JPEG REQUIRED)
#find_package(DevIL REQUIRED)

add_executable(engine ${SOURCE_FILES})

target_include_directories(engine PUBLIC ${OPENGL_INCLUDE_DIR} ../3rdparty/gl3w/include/ ../3rdparty/imgui/) #${PNG_INCLUDE_DIR} ${JPEG_INCLUDE_DIR} ${IL_INCLUDE_DIR})
target_link_libraries(engine ${OPENGL_gl_LIBRARY} gl3w imgui glfw glm dl) #${PNG_LIBRARY} ${JPEG_LIBRARIES} ${IL_LIBRARIES} ${ILU_LIBRARIES})

