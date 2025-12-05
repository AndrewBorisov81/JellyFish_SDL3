#pragma once

#include "GameStateMachine.h"

#include <memory>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// Smart pointer aliases for SDL objects
using SDLWindowPtr   = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using SDLRendererPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Game
{
private:
    // Private constructor/destructor for singleton
    Game() = default;
    ~Game() = default;

    // Singleton instance
    static Game* s_instance;

    // SDL resources
    SDLWindowPtr   m_window{nullptr, SDL_DestroyWindow};
    SDLRendererPtr m_renderer{nullptr, SDL_DestroyRenderer};

    // Game state machine
    std::unique_ptr<GameStateMachine> m_stateMachine;

    // Running flag
    bool m_isRunning = false;

public:
    // Singleton accessor
    static Game* Instance()
    {
        if (!s_instance)
            s_instance = new Game();
        return s_instance;
    }

    // Initialization
    bool init(const char* title, int width, int height, bool fullscreen);

    // Game loop
    void handleEvents();
    void update();
    void render();

    // Cleanup
    void clean();
    void quit() { m_isRunning = false; }

    // Getters
    bool running() const { return m_isRunning; }
    SDL_Renderer* getRenderer() const { return m_renderer.get(); }
    SDL_Window* getWindow() const { return m_window.get(); }

    GameStateMachine* getStateMachine() { return m_stateMachine.get(); }
};

typedef Game TheGame;



