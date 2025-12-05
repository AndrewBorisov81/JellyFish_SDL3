#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <map>

class TextureManager
{
public:
    // Singleton accessor
    static TextureManager* Instance()
    {
        if (s_Instance == nullptr)
            s_Instance = new TextureManager();
        return s_Instance;
    }

    // Load texture from file
    bool load(const std::string& fileName,
              const std::string& id,
              SDL_Renderer* pRenderer);

    // Draw full texture (SDL3)
    void draw(const std::string& id,
              int x, int y,
              int width, int height,
              SDL_Renderer* pRenderer,
              SDL_FlipMode flip = SDL_FLIP_NONE);

    // Draw animation frame (SDL3)
    void drawFrame(const std::string& id,
                   int x, int y,
                   int width, int height,
                   float angleRotation,
                   int currentRow, int currentFrame,
                   SDL_Renderer* pRenderer,
                   SDL_FlipMode flip = SDL_FLIP_NONE);

    // Remove texture by ID
    void clearFromTextureMap(const std::string& id);

private:
    TextureManager() = default;
    ~TextureManager() = default;

    static TextureManager* s_Instance;

    // id → texture
    std::map<std::string, SDL_Texture*> m_textureMap;
    SDL_Texture* m_currentTexture{ nullptr };
};

using TheTextureManager = TextureManager;
