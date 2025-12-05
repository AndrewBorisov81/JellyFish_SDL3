
#include "GameStateMachine.h"
#include "GameState.h"

void GameStateMachine::pushState(std::unique_ptr<GameState> state)
{
  m_gameStates.push_back(std::move(state));
  //m_gameStates.push_back(state);

  m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
  if (!m_gameStates.empty())
  {
    if (m_gameStates.back()->onExit())
    {
      //delete m_gameStates.back();
      m_gameStates.pop_back();
    }
  }
}

void GameStateMachine::changeState(std::unique_ptr<GameState> state) 
{
  if (!m_gameStates.empty())
  {
    //if it already exits don't do anything
    /*if (m_gameStates.back()->getStateID() == state->getStateID())
    {
        return;	//do nothing
    }*/

    if (m_gameStates.back()->onExit())
    {
      //delete m_gameStates.back();
      m_gameStates.pop_back();
    }
  }

  m_gameStates.push_back(std::move(state));

  m_gameStates.back()->onEnter();
}

void GameStateMachine::handleEvents()
{
  if (!m_gameStates.empty())
  {
    m_gameStates.back()->handleEvents();
  }
}

void GameStateMachine::update()
{
  if (!m_gameStates.empty())
  {
    m_gameStates.back()->update();
  }
}

void GameStateMachine::render()
{
  if (!m_gameStates.empty())
  {
    m_gameStates.back()->render();
  }
}

const std::vector<std::unique_ptr<GameState>>& GameStateMachine::getStates() const
{
    return m_gameStates;
}
