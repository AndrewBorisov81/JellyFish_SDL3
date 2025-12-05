#pragma once

#include "Point.h"
#include "Vector2D.h"
#include <functional>

class Size;

enum class State
{
  STOP,
  MOVE
};

class Mover
{
public:
  Mover();
  Mover(Vector2D endPoint);
  Mover(Vector2D endPoint, float speed);
  virtual ~Mover();

  virtual bool init();

  void setParameters(Vector2D endPoint, float speed);

  virtual void setState(State aState);
  State getState();

  virtual void update();
  virtual void move();

  virtual void startMove();
  virtual void stopMove();

  Vector2D calculateVelocity(Vector2D beginPoint, Vector2D endPoint, float speed);
  Vector2D calculateMoveDirection(Vector2D beginPoint, Vector2D endPoint);

  float getAngleRotation();

  Vector2D getMoveDirection();
  void setMoveDirection(Vector2D moveDirection);

  void setVelocity(Vector2D vel);
  Vector2D getVelocity();

  void setNewPosition(Vector2D newPos);
  Vector2D getNewPosition();

  void setBeginPoint(Vector2D beginPoint);
  void setEndPoint(Vector2D endPoint);
  void setCurrentPoint(Vector2D currentPoint);

  virtual void setObjectSize(Size objectSize);

  void setCallBackStopMoveEndPath(std::function<Vector2D(Point)>);
  std::function<Vector2D(Point)> m_callbackStopMoveEndPath;

protected:
  State m_state{ State::STOP };

  Vector2D m_initMoveDirection{ 0.0f, 0.0f };
  Vector2D m_moveDirection{ 0.0f, 0.0f };
  float m_speed{ 0.0f };

  Vector2D m_velocity{ 0.0f, 0.0f };

  Vector2D m_beginPoint{ 0.0f, 0.0f };
  Vector2D m_endPoint{ 0.0f, 0.0f };
  Vector2D m_currentPos{ 0.0f, 0.0f };
  Vector2D m_newPos{ 0.0f, 0.0f };

  float m_prevDist{ 0.0f };
  float m_curDist{ 0.0f };

  float m_angleRotation{ 0.0f };
};
