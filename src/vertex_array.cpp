//
// vertex_array.cpp
// Created by TheFatNinja 
// 01-05-2019
//

#include "vertex_array.h"

typedef struct
{
    float x, y;
    float r, g, b;
    float u, v;
} Vertex;

GLuint element_buffer[] = {
        0, 1, 2,
        2, 1, 3
};

VertexArray::VertexArray(const VertexData &data, const std::shared_ptr<ShaderProgram>& program) {
    array = 0, buffer = 0, elements = 0; // not necessary but silences warnings
    glGenVertexArrays(1, &array);
    glGenBuffers(1, &buffer);
    glGenBuffers(1, &elements);
    glBindVertexArray(array);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    Vertex vertices[] = {
            {0.f, 0.f, data.red, data.green, data.blue, data.uvx1, data.uvy1},
            {data.width, 0.f, data.red, data.green, data.blue, data.uvx2, data.uvy1},
            {0.f, data.height, data.red, data.green, data.blue, data.uvx1, data.uvy2},
            {data.width, data.height, data.red, data.green, data.blue, data.uvx2, data.uvy2}
    };
    program->Activate();
    GLint pos_location = program->GetLocation("pos");
    GLint col_location = program->GetLocation("col");
    GLint uv_location = program->GetLocation("uv");
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(pos_location);
    glVertexAttribPointer(pos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0);
    glEnableVertexAttribArray(col_location);
    glVertexAttribPointer(col_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*) (sizeof(float) * 2));
    glEnableVertexAttribArray(uv_location);
    glVertexAttribPointer(uv_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*) (sizeof(float) * 5));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer), element_buffer, GL_STATIC_DRAW);

}

VertexArray::~VertexArray() {
    glDeleteBuffers(1, &elements);
    glDeleteBuffers(1, &buffer);
    glDeleteVertexArrays(1, &array);
}

void VertexArray::Activate() {
    glBindVertexArray(array);
}
