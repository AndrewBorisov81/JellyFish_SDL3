
#pragma once

#include <string>
#include <SDL3/SDL.h>

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void handleEvents(const SDL_Event& e) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual const std::string getStateID() const = 0;
};
