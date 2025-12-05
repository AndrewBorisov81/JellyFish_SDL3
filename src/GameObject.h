#pragma once

#include "LoaderParams.h"

class Vector2D;

class GameObject
{
protected:
  GameObject() {}
  virtual ~GameObject() {}

public:
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;

  virtual void toDelete() = 0;
  virtual bool isClickable() = 0;
  virtual bool isToDelete() = 0;

  virtual int getWidth() = 0;
  virtual int getHeight() = 0;
  virtual Vector2D& getPosition() = 0;

  virtual void load(const LoaderParams& pParams) = 0;
};
