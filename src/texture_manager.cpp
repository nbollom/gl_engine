//
// texture_manager.cpp
// Created by TheFatNinja
// 16-04-2019
//

#include "texture_manager.h"
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

GLuint LoadTexture(const std::string &filename) {
    int bpp = 0;
    int width, height;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &bpp, 4);
    if (data == nullptr) {
        throw ImageLoadException(filename);
    }
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return texture_id;
}

std::shared_ptr<Texture> TextureManager::CreateTextureFromFile(const std::string &filename) {
    std::shared_ptr<Texture> t = std::make_shared<Texture>();
    t->texture_id = LoadTexture(filename);
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

void TextureManager::PreloadSpritesheetWithFixedSize(const std::string &filename, const int &width, const int &height) {
    if (this->fixed_size_spritesheet_textures.find(filename) == this->fixed_size_spritesheet_textures.end()) {
        auto *t = new FixedSizeSpritesheetTexture();
        t->texture_id = LoadTexture(filename);
        t->width = width;
        t->height = height;
        this->fixed_size_spritesheet_textures[filename] = t;
    }
}

void TextureManager::PreloadSpriteSheetWithDefinition(const std::string &filename, const std::string &definition_file) {
    // TODO: logic needed
}

std::shared_ptr<Texture> TextureManager::GetTexture(const std::string &filename) {
    if (this->textures.find(filename) == this->textures.end()) {
        return this->CreateTextureFromFile(filename);
    }
    return this->textures[filename];
}

std::shared_ptr<Texture> TextureManager::GetTextureFromFixedSizeSpritesheet(const std::string &filename, int x, int y) {
    FixedSizeSpritesheetTexture *t = fixed_size_spritesheet_textures[filename];
    if (t == nullptr) {
        throw std::runtime_error("Fixed size spritesheet not loaded");
    }
    return t->GetChild(x, y);
}

std::shared_ptr<Texture> TextureManager::GetTextureFromDefinedSpritesheet(const std::string &filename, const std::string &name) {
    // TODO: logic needed
    return std::shared_ptr<Texture>();
}

void TextureManager::UnloadTextures(const std::vector<std::string> &filenames) {
    for (const std::string& filename: filenames) {
        this->UnloadTexture(filename);
    }
}

void TextureManager::UnloadTexture(const std::string &filename) {
    if (this->textures.find(filename) != this->textures.end()) {
        if (this->textures[filename].use_count() == 1) {
            // Only unload if there are no other references
            // TODO: Is there a better way to do this?
            glDeleteTextures(1, &this->textures[filename]->texture_id);
            this->textures.erase(filename);
        }
    }
}

/*
    NSVGimage *image = NULL;
    NSVGrasterizer *rast = NULL;
    unsigned char* img = NULL;
    int w, h;
    const char* filename = "../example/23.svg";

    printf("parsing %s\n", filename);
    image = nsvgParseFromFile(filename, "px", 96.0f);
    if (image == NULL) {
        printf("Could not open SVG image.\n");
        goto error;
    }
    w = (int)image->width;
    h = (int)image->height;

    rast = nsvgCreateRasterizer();
    if (rast == NULL) {
        printf("Could not init rasterizer.\n");
        goto error;
    }

    img = malloc(w*h*4);
    if (img == NULL) {
        printf("Could not alloc image buffer.\n");
        goto error;
    }

    printf("rasterizing image %d x %d\n", w, h);
    nsvgRasterize(rast, image, 0,0,1, img, w, h, w*4);

    printf("writing svg.png\n");
    stbi_write_png("svg.png", w, h, 4, img, w*4);

error:
    nsvgDeleteRasterizer(rast);
    nsvgDelete(image);
*/
