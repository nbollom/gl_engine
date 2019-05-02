//
// main.cpp
// Created By TheFatNinja
// 12-04-2019
//

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdio>
#include <memory>
#include "scene.h"
#include "inlines.h"
#include "texture_manager.h"
#include "shader_program.h"
#include "vertex_manager.h"

float scale = 1;
const int design_width = 1024;
const int design_height = 768;
std::unique_ptr<Scene> *current_scene;

void glfw_error_callback(int error, const char *description) {
    printf("[ERROR %d]: %s", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    float view_width = width;
    float view_height = height;
    float xoffset = 0;
    float yoffset = 0;
    if ((float)design_width / design_height * view_height < view_width) {
        view_width = (float)design_width / design_height * view_height;
        xoffset = ((float)width - view_width) / 2;
    }
    else {
        view_height = (float)design_height / design_width * view_width;
        yoffset = ((float)height - view_height) / 2;
    }
    glViewport((int)xoffset, (int)yoffset, (int)view_width, (int)view_height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main() {
    if (!glfwInit()) {
        printf("failed to initialize GLFW.\n");
        return -1;
    }

    glfwSetErrorCallback(glfw_error_callback);
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "GL Engine", nullptr, nullptr);
    if (!window) {
        printf("failed to create window\n");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);


    if (gl3wInit()) {
        printf("failed to initialize OpenGL\n");
        return -1;
    }
    if (!gl3wIsSupported(3, 2)) {
        fprintf(stderr, "OpenGL 3.2 not supported\n");
        return -1;
    }

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION));

    auto shader_program = ShaderProgram::DefaultShader();
    auto vertex_manager = VertexManager::Default();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float scale_x;
    float scale_y;
    glfwGetWindowContentScale(window, &scale_x, &scale_y);
    scale = MIN(scale_x, scale_y) * 1.2;

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard
    // Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();

    io.FontGlobalScale = scale;
    auto font_default = io.Fonts->AddFontDefault();

    double previousTime = glfwGetTime();
    int frames = 0;
    int last_fps = 0;

    auto tm = TextureManager::GetDefaultManager();
    auto t1 = tm->GetTexture("resources/test1.png");
    auto t2 = tm->GetTexture("resources/test2.png");
    auto t3 = tm->GetTexture("resources/test3.png");
    auto t4 = tm->GetTexture("resources/test4.png");
    float sprite_size = 1.f / 30;

    auto vm = VertexManager::Default();
    VertexData vd1 = {150.f, 150.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f};
    VertexData vd2 = {150.f, 150.f, 1.f, 1.f, 1.f, sprite_size * 2, sprite_size * 1, sprite_size * 3, sprite_size * 2};
    auto va1 = vm->CreateVertexArray(shader_program, vd1);
    auto va2 = vm->CreateVertexArray(shader_program, vd2);
    auto va3 = vm->CreateVertexArray(shader_program, vd2);
    auto va4 = vm->CreateVertexArray(shader_program, vd2);

    glClearColor(0.f, 0.f, 0.f, 255);

    double last_time = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glfwMakeContextCurrent(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int stride = 10;
        int posx = stride;
        int posy = stride;
        int size = 150;

        glm::mat4x4 m, p, mvp;
        glm::vec3 pos = glm::vec3(posx, posy, 0);
        m = glm::translate(glm::mat4x4(1.f), pos);
        p = glm::ortho(0.0f, (float)design_width, (float)design_height, 0.f, -1.0f, 1.0f);
        mvp = p * m;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        shader_program->Activate();
        va1->Activate();
        GLint mvp_location = shader_program->GetLocation("mvp", true);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        t1->Activate();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        posx += size + stride;

        pos = glm::vec3(posx, posy, 0);
        m = glm::translate(glm::mat4x4(1.f), pos);
        mvp = p * m;
        shader_program->Activate();
        va2->Activate();
        mvp_location = shader_program->GetLocation("mvp", true);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        t2->Activate();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        posx += size + stride;

        pos = glm::vec3(posx, posy, 0);
        m = glm::translate(glm::mat4x4(1.f), pos);
        mvp = p * m;
        shader_program->Activate();
        va3->Activate();
        mvp_location = shader_program->GetLocation("mvp", true);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        t3->Activate();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        posx += size + stride;

        pos = glm::vec3(posx, posy, 0);
        m = glm::translate(glm::mat4x4(1.f), pos);
        mvp = p * m;
        shader_program->Activate();
        va4->Activate();
        mvp_location = shader_program->GetLocation("mvp", true);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        t4->Activate();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // fps code
        double currentTime = glfwGetTime();
        frames++;
        if (currentTime - previousTime >= 1.0) {
            last_fps = frames;
            frames = 0;
            previousTime = currentTime;
        }
        ImGui::SetNextWindowPos(ImVec2(0, 0));
//        ImGui::SetNextWindowSize(ImVec2(40 * scale, 25 * scale));
        ImGui::Begin("FPS Counter", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("%d", last_fps);
        ImGui::End();

        // render imgui stuff
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    tm->UnloadTexture("resources/test1.png");
    tm->UnloadTexture("resources/test2.png");
    tm->UnloadTexture("resources/test3.png");
    tm->UnloadTexture("resources/test4.png");
    va1 = va2 = va3 = va4 = nullptr;
    shader_program = nullptr;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
