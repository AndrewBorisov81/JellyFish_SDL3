#include "TextureManager.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include <string>

#if defined(_WIN32)
#include <windows.h>

#elif defined(__APPLE__)
#include <mach-o/dyld.h>   // MUST be included at top level

#else
#include <unistd.h>
#endif

TextureManager* TextureManager::s_Instance = nullptr;

// -----------------------------------------------------------
// Cross-platform executable directory (Windows / macOS / Linux)
// -----------------------------------------------------------
std::string GetExecutableDir()
{
#if defined(_WIN32)

    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    return std::filesystem::path(buffer).parent_path().string();

#elif defined(__APPLE__)

    char buffer[1024];
    uint32_t size = sizeof(buffer);
    _NSGetExecutablePath(buffer, &size);

    char realPath[PATH_MAX];
    realpath(buffer, realPath);

    std::string path(realPath);
    return path.substr(0, path.find_last_of('/'));

#else  // Linux

    std::string exe = std::filesystem::read_symlink("/proc/self/exe");
    return std::filesystem::path(exe).parent_path().string();

#endif
}

// -----------------------------------------------------------
// LOAD TEXTURE
// -----------------------------------------------------------
bool TextureManager::load(const std::string& fileName,
                          const std::string& id,
                          SDL_Renderer* pRenderer)
{
    // Build absolute texture path
    std::string path = GetExecutableDir() + fileName;

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface)
    {
        SDL_Log("IMG_Load failed: %s", SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    SDL_DestroySurface(surface);

    if (!texture)
    {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        return false;
    }

    std::map<std::string, SDL_Texture*>::iterator it = m_textureMap.find(id);

    if(texture !=0 && it == m_textureMap.end()) {
        m_textureMap[id] = texture;
        return true;
    }
    return false;
}

// -----------------------------------------------------------
// DRAW TEXTURE (SDL3)
// -----------------------------------------------------------
void TextureManager::draw(const std::string& id,
                          int x, int y, int width, int height,
                          SDL_Renderer* pRenderer,
                          SDL_FlipMode flip)
{
    if (m_textureMap.find(id) == m_textureMap.end())
        return;

    if (m_currentTexture == nullptr)
        m_currentTexture = m_textureMap[id];

    SDL_FRect srcRect = { 0, 0, (float)width, (float)height };
    SDL_FRect destRect = { (float)x, (float)y, (float)width, (float)height };

    SDL_RenderTextureRotated(
        pRenderer,
        m_textureMap[id],
        nullptr,
        &destRect,
        0.0,       // no rotation
        nullptr,
        flip
    );
}

// -----------------------------------------------------------
// DRAW ANIMATION FRAME (SDL3)
// -----------------------------------------------------------
void TextureManager::drawFrame(const std::string& id,
                               int x, int y,
                               int width, int height,
                               float angleRotation,
                               int currentRow, int currentFrame,
                               SDL_Renderer* pRenderer,
                               SDL_FlipMode flip)
{
    if (m_textureMap.find(id) == m_textureMap.end())
        return;

       SDL_FRect src = {
        0.0f,                          // X always 0 for vertical sheet
        (float)(height * currentFrame),  // Y down by frame height
        (float)width,
        (float)height
    };

    SDL_FRect dst = {
        (float)x, (float)y,
        (float)width, (float)height
    };

    SDL_FPoint center = { width / 2.0f, height / 2.0f };

    SDL_RenderTextureRotated(
        pRenderer,
        m_textureMap[id],
        &src,
        &dst,
        angleRotation,
        &center,
        flip
    );
}

// -----------------------------------------------------------
// CLEAR FROM MAP
// -----------------------------------------------------------
void TextureManager::clearFromTextureMap(const std::string& id)
{
    auto it = m_textureMap.find(id);
    if (it == m_textureMap.end()) return;

    SDL_DestroyTexture(it->second);
    m_textureMap.erase(it);
}
