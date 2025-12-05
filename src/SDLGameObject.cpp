
#include "SDLGameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "Constants.h"

SDLGameObject::SDLGameObject() : GameObject()
{
  m_textureManager = TextureManager::Instance();
  m_angleRotation = 0;
}

SDLGameObject::~SDLGameObject()
{
  
}

void SDLGameObject::draw()
{
  TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), 
      (int)m_position.getY(), m_width, m_height, m_angleRotation, m_currentRow, 
          m_currentFrame, TheGame::Instance()->getRenderer());
}

void SDLGameObject::update()
{
  m_velocity += m_acceleration;
  m_position += m_velocity;
}

void SDLGameObject::clean()
{
  //blank
}

void SDLGameObject::setVelocity(const Vector2D& vel)
{
  m_velocity = vel;
}

void SDLGameObject::setAngleRotation(float angleRotation)
{
  m_angleRotation = angleRotation;
}


void SDLGameObject::setPosition(const Vector2D& pos)
{
  m_position = pos;
}

void SDLGameObject::load(const LoaderParams& pParams)
{
  m_position = Vector2D(pParams.getX(), pParams.getY());
  m_velocity = Vector2D(0, 0);
  m_acceleration = Vector2D(0, 0);
  m_width = pParams.getWidth();
  m_height = pParams.getHeight();
  m_textureID = pParams.getTextureID();
  m_currentRow = 1;
  m_currentFrame = 1;
  m_numFrames = pParams.getNumFrames();

  m_textureManager->load(TEXTURE_PATH, m_textureID, TheGame::Instance()->getRenderer());
}
