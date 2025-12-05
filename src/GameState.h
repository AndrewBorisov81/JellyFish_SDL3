
#pragma once

#include <string>

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual const std::string getStateID() const = 0;
};
