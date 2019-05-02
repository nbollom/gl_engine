//
// vertex_manager.h
// Created by TheFatNinja 
// 29-04-2019
//

#ifndef GL_ENGINE_VERTEX_MANAGER_H
#define GL_ENGINE_VERTEX_MANAGER_H

#include <unordered_map>
#include <memory>
#include "vertex_array.h"

class VertexManager {

private:
    std::unordered_map<VertexData, std::shared_ptr<VertexArray>> vertex_cache;


public:
    VertexManager() = default;

    static std::shared_ptr<VertexManager> Default();
    std::shared_ptr<VertexArray> CreateVertexArray(std::shared_ptr<ShaderProgram> &shader_program, VertexData &vertex_data);
};

#endif //GL_ENGINE_VERTEX_MANAGER_H
