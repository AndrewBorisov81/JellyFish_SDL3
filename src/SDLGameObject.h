
#pragma once

#include "GameObject.h"
#include "Vector2D.h"

class TextureManager;

class SDLGameObject : public GameObject
{
protected:

  Vector2D m_position;
  Vector2D m_velocity;
  Vector2D m_acceleration;

  float m_angleRotation;

  int m_width;
  int m_height;

  int m_currentRow;
  int m_currentFrame;
  int m_numFrames;
  int m_callbackID;

  bool m_isClickable{ true };
  bool m_isToDelete;

  TextureManager* m_textureManager;
  std::string m_textureID;

public:

  SDLGameObject();
  virtual ~SDLGameObject();

  virtual void draw() override;
  virtual void update() override;
  virtual void clean() override;

  Vector2D& getPosition() override { return m_position; }
  void setPosition(const Vector2D& pos);

  void setVelocity(const Vector2D& vel);

  void setAngleRotation(float angleRotation);

  int getWidth() override { return m_width; }
  int getHeight() override { return m_height; }

  bool isClickable() override { return m_isClickable; }
  bool isToDelete() override { return m_isToDelete; }
  void toDelete() override { m_isToDelete = true; }

  virtual void load(const LoaderParams& pParams) override;
};
