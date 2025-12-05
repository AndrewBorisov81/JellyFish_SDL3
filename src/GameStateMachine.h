
#pragma once

#include "IGameState.h"

#include <memory>
#include <vector>

class GameStateMachine
{
private:
    std::vector<std::unique_ptr<IGameState>> m_gameStates;
public:
    void popState();
    void pushState(std::unique_ptr<IGameState> state);
    void changeState(std::unique_ptr<IGameState> state);

    void handleEvents(const SDL_Event& e);
    void update();
    void render();

    const std::vector<std::unique_ptr<IGameState>>& getStates() const ;
};
