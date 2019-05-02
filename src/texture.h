//
// texture.h
// Created by TheFatNinja 
// 16-04-2019
//

#ifndef GL_ENGINE_TEXTURE_H
#define GL_ENGINE_TEXTURE_H

#include <GL/gl3w.h>

struct Texture {
    GLuint texture_id;
    int width;
    int height;

    bool operator==(const Texture &other) const {
        return texture_id == other.texture_id;
    }

    void Activate() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }
};

#endif //GL_ENGINE_TEXTURE_H
