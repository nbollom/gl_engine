//
// texture_manager.cpp
// Created by TheFatNinja
// 16-04-2019
//

#include "texture_manager.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/gl3w.h>

ImageLoadException::ImageLoadException(const std::string &filename) : std::runtime_error(std::string("Error loading file: ") + filename) {
    this->filename = filename;
}

std::string ImageLoadException::GetFilename() {
    return this->filename;
}


std::shared_ptr<TextureManager> default_texture_manager;

TextureManager::TextureManager() {
    // Do I need this?
}

TextureManager::~TextureManager() {

}

std::shared_ptr<TextureManager> TextureManager::GetDefaultManager() {
    if (default_texture_manager == nullptr) {
        default_texture_manager = std::make_shared<TextureManager>();
    }
    return default_texture_manager;
}

std::shared_ptr<Texture> TextureManager::CreateTextureFromFile(const std::string &filename) {
    std::shared_ptr<Texture> t = std::make_shared<Texture>();
    int bpp = 0;
    unsigned char *data = stbi_load(filename.c_str(), &t->width, &t->height, &bpp, 4);
    if (data == nullptr) {
        throw ImageLoadException(filename);
    }
    glGenTextures(1, &t->texture_id);
    glBindTexture(GL_TEXTURE_2D, t->texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->width, t->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    this->textures[filename] = t;
    return t;
}

void TextureManager::PreloadTextures(const std::vector<std::string> &filenames) {
    for (const std::string& filename: filenames) {
        if (this->textures.find(filename) == this->textures.end()) {
            this->CreateTextureFromFile(filename);
        }
    }
}

std::shared_ptr<Texture> TextureManager::GetTexture(const std::string &filename) {
    if (this->textures.find(filename) == this->textures.end()) {
        return this->CreateTextureFromFile(filename);
    }
    return this->textures[filename];
}

void TextureManager::UnloadTextures(const std::vector<std::string> &filenames) {
    for (const std::string& filename: filenames) {
        this->UnloadTexture(filename);
    }
}

void TextureManager::UnloadTexture(const std::string &filename) {
    if (this->textures.find(filename) != this->textures.end()) {
        glDeleteTextures(1, &this->textures[filename]->texture_id);
        this->textures.erase(filename);
    }
}
