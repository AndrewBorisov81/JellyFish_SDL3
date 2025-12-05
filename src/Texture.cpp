#include "Texture.h"

Texture::Texture() : m_texture(nullptr), m_width(0), m_height(0) {}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, const std::string& path) {
    free(); // free previous texture

    SDL_Surface* surf = IMG_Load(path.c_str());
    if (!surf) {
        std::cerr << "IMG_Load failed: " << SDL_GetError() << "\n";
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (!m_texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << "\n";
        SDL_DestroySurface(surf);
        return false;
    }

    m_width = surf->w;
    m_height = surf->h;

    SDL_DestroySurface(surf);
    return true;
}

void Texture::free() {
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;
    }
}

void Texture::render(SDL_Renderer* renderer, float x, float y, float w, float h) {
    if (!m_texture) return;

    SDL_FRect dst;
    dst.x = x;
    dst.y = y;
    dst.w = (w > 0 ? w : static_cast<float>(m_width));
    dst.h = (h > 0 ? h : static_cast<float>(m_height));

    SDL_RenderTexture(renderer, m_texture, nullptr, &dst);
}

int Texture::getWidth() const { return m_width; }
int Texture::getHeight() const { return m_height; }
SDL_Texture* Texture::get() const { return m_texture; }
