#include "Mover.h"
#include "Math2.h"
#include "Easing.h"
#include "Size.h"

Mover::Mover()
{
  setState(State::STOP);
}

Mover::Mover(Vector2D endPoint, float speed) : m_endPoint(endPoint), m_speed(speed)
{
  setState(State::STOP);
}

Mover::Mover(Vector2D endPoint) : m_endPoint(endPoint)
{
  setState(State::STOP);
}

Mover::~Mover()
{
}

bool Mover::init()
{
  m_initMoveDirection.setX(0);
  m_initMoveDirection.setY(1);

  return true;
}

void Mover::setParameters(Vector2D endPoint, float speed)
{
  m_endPoint = endPoint;
  m_speed = speed;
}

void Mover::setState(State aState)
{
  m_state = aState;

  switch (m_state)
  {
  case State::MOVE:
  {
    Vector2D velocity(calculateVelocity(m_beginPoint, m_endPoint, m_speed));
    setVelocity(velocity);
    m_moveDirection = calculateMoveDirection(m_beginPoint, m_endPoint);
    m_prevDist = Math2::distance(m_endPoint.getX(), m_endPoint.getX(), m_currentPos.getX(), m_currentPos.getY());
    m_angleRotation = (m_initMoveDirection.getAngle(m_moveDirection) * 180 / M_PI) - 180;
  }
    break;

  case State::STOP:
    m_velocity.Zero();
    break;
  }
}

State Mover::getState()
{
  return m_state;
}

void Mover::update()
{
  
}

void Mover::move()
{
  switch (m_state)
  {
  case State::MOVE:
  {
    m_curDist = Math2::distance(m_endPoint.getX(), m_endPoint.getY(), m_currentPos.getX(), m_currentPos.getY());

    if (m_prevDist < m_curDist)
    {
      setState(State::STOP);
    }

    m_prevDist = m_curDist;
  }
  break;

  case State::STOP:
    break;
  }
}

void Mover::startMove()
{
  setState(State::MOVE);
}

void Mover::stopMove()
{
  setState(State::STOP);
}

Vector2D Mover::calculateVelocity(Vector2D beginPoint, Vector2D endPoint, float speed)
{
  Vector2D velocityDir(endPoint.getX() - beginPoint.getX(), endPoint.getY() - beginPoint.getY());
  velocityDir.normalize();

  return Vector2D(velocityDir.getX() * speed, velocityDir.getY() * speed);
}

Vector2D Mover::calculateMoveDirection(Vector2D beginPoint, Vector2D endPoint)
{
  Vector2D moveDirection(endPoint.getX() - beginPoint.getX(), endPoint.getY() - beginPoint.getY());
  moveDirection.normalize();

  return Vector2D(moveDirection.getX(), moveDirection.getY());
}

float Mover::getAngleRotation()
{
  return m_angleRotation;
}

Vector2D Mover::getMoveDirection()
{
  return m_moveDirection;
}

void Mover::setMoveDirection(Vector2D moveDirection)
{
  m_moveDirection = moveDirection;
}

void Mover::setVelocity(Vector2D vel)
{
  m_velocity.setX(vel.getX());
  m_velocity.setY(vel.getY());
}

void Mover::setBeginPoint(Vector2D beginPoint)
{
  m_beginPoint = beginPoint;
}

void Mover::setEndPoint(Vector2D endPoint)
{
  m_endPoint = endPoint;
}

void Mover::setCurrentPoint(Vector2D currentPoint)
{
  m_currentPos = currentPoint;
}

void Mover::setObjectSize(Size objectSize)
{
}

void Mover::setCallBackStopMoveEndPath(std::function<Vector2D(Point)> callBackStopMoveEndPath)
{
  m_callbackStopMoveEndPath = callBackStopMoveEndPath;
}

Vector2D Mover::getVelocity()
{
  return Vector2D(m_velocity.getX(), m_velocity.getY());
}

void Mover::setNewPosition(Vector2D newPos)
{
  m_newPos.setX(newPos.getX());
  m_newPos.setY(newPos.getY());
}

Vector2D Mover::getNewPosition()
{
  return m_newPos;
}
