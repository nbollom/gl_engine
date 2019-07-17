//
// texture_manager.h
// Created by TheFatNinja
// 16-04-2019
//

#ifndef GL_ENGINE_TEXTURE_MANAGER_H
#define GL_ENGINE_TEXTURE_MANAGER_H

#include <memory>
#include <map>
#include <vector>
#include <string>
#include "texture.h"

class ImageLoadException : public std::runtime_error {

private:
    std::string filename;

public:
    explicit ImageLoadException(const std::string &filename);
    std::string GetFilename();
};

class TextureManager {

private:
    std::map<std::string, std::shared_ptr<Texture>> textures;
    std::map<std::string, FixedSizeSpritesheetTexture*> fixed_size_spritesheet_textures;

public:
    TextureManager();
    virtual ~TextureManager();
    static std::shared_ptr<TextureManager> GetDefaultManager();

    void PreloadTextures(const std::vector<std::string> &filenames);
    void PreloadSpritesheetWithFixedSize(const std::string &filename, const int &width, const int &height);
    void PreloadSpriteSheetWithDefinition(const std::string &filename, const std::string &definition_file);
    std::shared_ptr<Texture> GetTexture(const std::string &filename);
    std::shared_ptr<Texture> GetTextureFromFixedSizeSpritesheet(const std::string &filename, int x, int y);
    std::shared_ptr<Texture> GetTextureFromDefinedSpritesheet(const std::string &filename, const std::string &name);
    void UnloadTextures(const std::vector<std::string> &filenames);
    void UnloadTexture(const std::string &filename);

private:
    std::shared_ptr<Texture> CreateTextureFromFile(const std::string &filename);

};

#endif //GL_ENGINE_TEXTURE_MANAGER_H
