#include "JellyFish.h"
#include "Vector2D.h"
#include "Game.h"
#include "Mover.h"
#include "LoaderParams.h"
#include "Constants.h"
#include "Size.h"

JellyFish::JellyFish()
{

}

JellyFish::JellyFish(int x, int y, Mover* mover)
{
  LoaderParams loaderParams(x, y, JELLY_FISH_WIDTH, JELLY_FISH_HEIGHT, TEXTURE_ID, TEXTURE_FRAMES);
  load(loaderParams);

  if (mover)
  {
    m_mover = mover;
    m_mover->setObjectSize(Size(getHeight(), getWidth()));
    m_mover->setBeginPoint(getPosition());
    m_mover->setCurrentPoint(getPosition());
    m_mover->init();
    m_mover->startMove();
  }
}

JellyFish::~JellyFish()
{
  delete m_mover;
}

void JellyFish::draw()
{
  SDLGameObject::draw();
}

void JellyFish::update()
{
  m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

  SDLGameObject::update();

  if (m_mover)
  {
    m_mover->update();
    m_mover->move();
    m_mover->setCurrentPoint(getPosition());
    Vector2D nP = m_mover->getNewPosition();
    setPosition(m_mover->getNewPosition());
    setAngleRotation(m_mover->getAngleRotation());
  }
}

void JellyFish::clean()
{
}

GameObject* JellyFish::create(int x, int y, Mover* mover)
{
  return new JellyFish(x, y, mover);
}

Mover* JellyFish::getMover()
{
  return m_mover;
}
