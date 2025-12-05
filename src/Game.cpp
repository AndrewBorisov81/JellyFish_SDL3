#include "Game.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "Texture.h"
#include "GameObject.h"  // Needed for reportLeaks
#include <iostream>

// Initialize singleton
Game* Game::s_instance = nullptr;

// Some environments / versions may define IMG_InitFlags_PNG differently
#ifndef IMG_INIT_PNG
#ifdef IMG_InitFlags_PNG
#define IMG_INIT_PNG IMG_InitFlags_PNG
#else
#define IMG_INIT_PNG 0
#endif
#endif

bool Game::init(const char* title, int width, int height, bool fullscreen)
{
    Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_image for PNG
if (IMG_INIT_PNG != 0) {
    if ((SDL_WasInit(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
        std::cerr << "SDL_ImageInit failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
}

    // Create SDL window
    SDL_Window* wnd = SDL_CreateWindow(title, width, height, flags);
    if (!wnd) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    m_window.reset(wnd);

    // Create SDL renderer
    SDL_Renderer* rnd = SDL_CreateRenderer(m_window.get(), nullptr);
    if (!rnd) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        m_window.reset();
        SDL_Quit();
        return false;
    }
    m_renderer.reset(rnd);

    // Set a default gray background
    SDL_SetRenderDrawColor(m_renderer.get(), 50, 50, 50, 255);

    // Initialize GameStateMachine with PlayState
    m_stateMachine = std::make_unique<GameStateMachine>();
    m_stateMachine->pushState(std::make_unique<PlayState>());
    //m_stateMachine->pushState(new PlayState());

    m_isRunning = true;
    return true;
}

void Game::handleEvents(const SDL_Event& e)
{
    //if (e.type == SDL_EVENT_QUIT) m_isRunning = false;

    if (m_stateMachine)
        m_stateMachine->handleEvents(e);
}

void Game::update()
{
    if (m_stateMachine)
        m_stateMachine->update();
}

void Game::render()
{
    if (!m_renderer) return;

    SDL_RenderClear(m_renderer.get());

    if (m_stateMachine)
        m_stateMachine->render();

    SDL_RenderPresent(m_renderer.get());
}

void Game::clean()
{
    if (m_stateMachine) m_stateMachine.reset();

    // Reset SDL objects
    if (m_renderer) m_renderer.reset();
    if (m_window) m_window.reset();

    // Quit SDL_image and SDL
    SDL_Quit();
}
