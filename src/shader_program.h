//
// shader_program.h
// Created by TheFatNinja 
// 01-05-2019
//

#ifndef GL_ENGINE_SHADER_PROGRAM_H
#define GL_ENGINE_SHADER_PROGRAM_H

#include <GL/gl3w.h>
#include <stdexcept>
#include <map>
#include <memory>

class ShaderCompileError : public std::runtime_error {

public:
    ShaderCompileError(const char *error);
};

class ShaderProgram {

private:
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    std::map<const char*, GLint> location_cache;

public:
    ShaderProgram(const char *vertex_shader_text, const char *fragment_shader_text);
    ~ShaderProgram();

    void Activate();
    GLint GetLocation(const char *name, bool uniform = false);

    static std::shared_ptr<ShaderProgram> DefaultShader();

};

#endif //GL_ENGINE_SHADER_PROGRAM_H
