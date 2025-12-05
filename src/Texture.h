#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>

class Texture
{
private:
    SDL_Texture* m_texture = nullptr;
    int m_width = 0;
    int m_height = 0;

public:
    Texture();
    ~Texture();

    bool loadFromFile(SDL_Renderer* renderer, const std::string& path);
    void free();
    void render(SDL_Renderer* renderer, float x, float y, float w = 0, float h = 0);

    int getWidth() const;
    int getHeight() const;
    SDL_Texture* get() const;
};
