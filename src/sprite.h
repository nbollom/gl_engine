//
// sprite.h
// Created by TheFatNinja 
// 03-05-2019
//

#ifndef GL_ENGINE_SPRITE_H
#define GL_ENGINE_SPRITE_H

#include "texture.h"
#include "vertex_array.h"

class Sprite {

private:
    std::shared_ptr<Texture> texture;
    std::shared_ptr<VertexArray> vertex_array;

public:
    Sprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture);
    ~Sprite();

};

#endif //GL_ENGINE_SPRITE_H
