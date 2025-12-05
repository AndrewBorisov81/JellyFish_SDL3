#pragma once

#include "SDLGameObject.h"

class Vector2D;
class Game;
class Mover;

class JellyFish : public SDLGameObject
{
public:
  JellyFish();
  JellyFish(int x, int y, Mover* mover = nullptr);
  virtual ~JellyFish();

  void draw() override;
  void update() override;
  void clean() override;

  static GameObject* create(int x, int y, Mover* mover = nullptr);

  Mover* getMover();

private:
  Mover* m_mover{ nullptr };
};
