//
// shader_program.cpp
// Created by TheFatNinja 
// 01-05-2019
//

#include "shader_program.h"

ShaderCompileError::ShaderCompileError(const char *error) : runtime_error(error) {

}

ShaderProgram::ShaderProgram(const char *vertex_shader_text, const char *fragment_shader_text) {
    GLchar log[1024];
    GLsizei log_length;
    GLint res = GL_FALSE;
    program = vertex_shader = fragment_shader = 0;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE) {
        glGetShaderInfoLog(vertex_shader, sizeof(GLchar) * 1024, &log_length, log);
        throw ShaderCompileError(log);
    }
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE) {
        glGetShaderInfoLog(fragment_shader, sizeof(GLchar) * 1024, &log_length, log);
        throw ShaderCompileError(log);
    }
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
}

ShaderProgram::~ShaderProgram() {
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
}

void ShaderProgram::Activate() {
    glUseProgram(program);
}

GLint ShaderProgram::GetLocation(const char *name, bool uniform) {
    if (location_cache.find(name) == location_cache.end()) {
        GLint location = 0;
        if (uniform) {
            location = glGetUniformLocation(program, name);
        }
        else {
            location = glGetAttribLocation(program, name);
        }
        location_cache[name] = location;
    }
    return location_cache[name];
}

//std::shared_ptr<ShaderProgram> default_shader = nullptr;

std::shared_ptr<ShaderProgram> ShaderProgram::DefaultShader() {
//    if (default_shader == nullptr) {
        static const char* vertex_shader_text =
                "#version 330 core\n"
                "uniform mat4 mvp;\n"
                "in vec2 pos;\n"
                "in vec3 col;\n"
                "in vec2 uv;\n"
                "out vec3 color;\n"
                "out vec2 fuv;\n"
                "void main() {\n"
                "    color = col;\n"
                "    fuv = uv;\n"
                "    gl_Position = mvp * vec4(pos, 0.0, 1.0);\n"
                "}\n";

        static const char* fragment_shader_text =
                "#version 330 core\n"
                "in vec3 color;\n"
                "in vec2 fuv;\n"
                "uniform sampler2D tex;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = texture(tex, fuv) * vec4(color, 1.0);\n"
                "}\n";
//        default_shader = std::make_shared<ShaderProgram>(vertex_shader_text, fragment_shader_text);
//    }
//    return default_shader;
return std::make_shared<ShaderProgram>(vertex_shader_text, fragment_shader_text);
}
