//
// vertex_array.h
// Created by TheFatNinja 
// 01-05-2019
//

#ifndef GL_ENGINE_VERTEX_ARRAY_H
#define GL_ENGINE_VERTEX_ARRAY_H

#include <algorithm>
#include <GL/gl3w.h>
#include <unordered_map>
#include "shader_program.h"

struct VertexData {
    float width;
    float height;
    float red;
    float green;
    float blue;
    float uvx1;
    float uvy1;
    float uvx2;
    float uvy2;

    bool operator==(const VertexData &other) const {
        return width == other.width &&
               height == other.height &&
               red == other.red &&
               green == other.green &&
               blue == other.blue &&
               uvx1 == other.uvx1 &&
               uvy1 == other.uvy1 &&
               uvx2 == other.uvx2 &&
               uvy2 == other.uvy2;
    }
};

namespace std {
    template<>
    struct hash<VertexData> {
        std::size_t operator()(const VertexData &vd) const {
            hash<float> hasher;
            size_t res = 17;
            res = res * 31 + hasher(vd.width);
            res = res * 31 + hasher(vd.height);
            res = res * 31 + hasher(vd.red);
            res = res * 31 + hasher(vd.green);
            res = res * 31 + hasher(vd.blue);
            res = res * 31 + hasher(vd.uvx1);
            res = res * 31 + hasher(vd.uvy1);
            res = res * 31 + hasher(vd.uvx2);
            res = res * 31 + hasher(vd.uvy2);
            return res;
        }
    };
}

class VertexArray {
private:
    GLuint array;
    GLuint buffer;
    GLuint elements;

public:
    explicit VertexArray(const VertexData &data, const std::shared_ptr<ShaderProgram>& program);
    ~VertexArray();

    void Activate();
};

#endif //GL_ENGINE_VERTEX_ARRAY_H
