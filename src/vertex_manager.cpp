//
// vertex_manager.cpp
// Created by TheFatNinja 
// 29-04-2019
//

#include "vertex_manager.h"

std::shared_ptr<VertexManager> default_vertex_manager = nullptr;

std::shared_ptr<VertexManager> VertexManager::Default() {
    if (default_vertex_manager == nullptr) {
        default_vertex_manager = std::make_shared<VertexManager>();
    }
    return default_vertex_manager;
}

std::shared_ptr<VertexArray> VertexManager::CreateVertexArray(std::shared_ptr<ShaderProgram> &shader_program, VertexData &vertex_data) {
    std::shared_ptr<VertexArray> array = vertex_cache[vertex_data];
    if (array == nullptr) {
        array = std::make_shared<VertexArray>(vertex_data, shader_program);
    }
    return array;
}
