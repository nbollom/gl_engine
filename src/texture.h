//
// texture.h
// Created by TheFatNinja 
// 16-04-2019
//

#ifndef GL_ENGINE_TEXTURE_H
#define GL_ENGINE_TEXTURE_H

#include <GL/gl3w.h>
#include <map>
#include <memory>

struct Texture {
    GLuint texture_id;
    GLfloat x1, x2, y1, y2;

    bool operator==(const Texture &other) const {
        return texture_id == other.texture_id && x1 == other.x1 && x2 == other.x2 && y1 == other.y1 && y2 == other.y2;
    }

    void Activate() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }
};

struct FixedSizeSpritesheetTexture {
    GLuint texture_id;
    int width, height;

    std::map<std::pair<int, int>, std::shared_ptr<Texture>> children;

    std::shared_ptr<Texture> GetChild(int x, int y) {
        std::pair<int, int> index = std::make_pair(x, y);
        if (children.find(index) == children.end()) {
            auto child = std::make_shared<Texture>();
            child->texture_id = texture_id;
            float texture_width = (float)width / 1.f;
            float texture_height = (float)height / 1.f;
            child->x1 = texture_width * x;
            child->x2 = child->x1 + texture_width;
            child->y1 = texture_height * y;
            child->y2 = child->y1 + texture_height;
            children[index] = child;
        }
        return children[index];
    }
};



#endif //GL_ENGINE_TEXTURE_H
