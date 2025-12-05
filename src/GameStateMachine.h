
#pragma once

#include "GameState.h"

#include <memory>
#include <vector>

class GameStateMachine
{
private:
    std::vector<std::unique_ptr<GameState>> m_gameStates;
    //std::vector<GameState*> m_gameStates;
public:
    void popState();
    void pushState(std::unique_ptr<GameState> state);
    void changeState(std::unique_ptr<GameState> state);
    //void pushState(GameState* state);
    //void changeState(GameState* state);

    void handleEvents(const SDL_Event& e);
    void update();
    void render();

    const std::vector<std::unique_ptr<GameState>>& getStates() const ;
};
