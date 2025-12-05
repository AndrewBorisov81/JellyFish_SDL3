#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "JellyFishMover.h"
#include "Size.h"
#include "Easing.h"
#include"Math2.h"

JellyFishMover::JellyFishMover()
{
  
}

JellyFishMover::JellyFishMover(Vector2D endPoint) : Mover(endPoint)
{
  
}

JellyFishMover::~JellyFishMover()
{

}

bool JellyFishMover::init()
{
  Mover::init();

  Vector2D directionVector;
  directionVector.setX(m_endPoint.getX() - m_beginPoint.getX());
  directionVector.setY(m_endPoint.getY() - m_beginPoint.getY());
  directionVector.normalize();

  m_moveDirection.setX(directionVector.getX());
  m_moveDirection.setY(directionVector.getY());

  m_newPos.setX(0.0f);
  m_newPos.setY(0.0f);

  m_timerEasing = 0.0f;
  m_maxDist = 0.0f;
  m_deltaShiftPath = 0.0f;

  m_indexCurrentPoint = 0;

  m_toMovePoints.clear();
  m_lengthSegments.clear();

  calculateToMovePoints(m_toMovePoints, m_beginPoint, m_endPoint, m_objectMaxLength);
  calculateLengthSegments(m_lengthSegments, m_toMovePoints, m_beginPoint);

  return true;
}

void JellyFishMover::tick()
{
  uint32_t tick_time = SDL_GetTicks();
  delta = float(tick_time - last_tick_time) / 1000;
  last_tick_time = tick_time;
}

void JellyFishMover::update()
{
  tick();
  Mover::update();
}

void JellyFishMover::move()
{
  switch (m_state)
  {
  case State::MOVE:
  {
    if (m_timerEasing < 1.0f)
    {
      if (delta > 1.0f)
        delta = 0;
      m_timerEasing += delta;
    }
    else
    {
      m_timerEasing = 1;
    }
    m_curDist = Math2::distance(m_endPoint.getX(), m_endPoint.getY(), m_currentPos.getX(), m_currentPos.getY());

    float m_easingRatio = Easing::easeInOutQuad(m_timerEasing);

    m_deltaShiftPath = m_easingRatio * m_maxDist;

    setNewPosition(Vector2D(m_beginPoint.getX() + m_moveDirection.getX() * m_deltaShiftPath, m_beginPoint.getY() + m_moveDirection.getY() * m_deltaShiftPath));

    if (m_timerEasing == 1)
    {
      setNewPosition(Vector2D(m_endPoint.getX(), m_endPoint.getY()));

      setState(State::STOP);
    }

    m_prevDist = m_curDist;
  }
    break;

  case State::STOP:
    break;
  }
}

void JellyFishMover::startMove()
{
  setState(State::MOVE);
}

void JellyFishMover::stopMove()
{
  setState(State::STOP);
}

void JellyFishMover::setObjectSize(Size objectSize)
{
  m_objectMaxLength = (objectSize.h >= objectSize.w) ? objectSize.h : objectSize.w;
}

void JellyFishMover::calculateToMovePoints(std::vector<Vector2D>& toMovePoints, Vector2D beginPoint, Vector2D endPoint, float objectLength)
{
  float distToEndPoint = Math2::distance(endPoint.getX(), endPoint.getY(), beginPoint.getX(), beginPoint.getY());

  int countSegments(0);
  if (objectLength > 0)
  {
    countSegments = (static_cast<int>(distToEndPoint)) / (static_cast<int>(2 * objectLength));
  }

  Vector2D directionVector((endPoint.getX() - beginPoint.getX()), (endPoint.getY() - beginPoint.getY()));
  directionVector.normalize();

  Vector2D oneSegment(directionVector.getX() * 2 * objectLength, directionVector.getY() * 2 * objectLength);

  Vector2D prevPoint(beginPoint.getX(), beginPoint.getY());
  for (int i = 0; i < countSegments; i++)
  {
    Vector2D point((prevPoint.getX() + oneSegment.getX()), (prevPoint.getY() + oneSegment.getY()));

    toMovePoints.push_back(point);

    prevPoint.setX(point.getX());
    prevPoint.setY(point.getY());
  }
  toMovePoints.push_back(endPoint);
}

void JellyFishMover::calculateLengthSegments(std::vector<float>& m_lengthSegments, const std::vector<Vector2D>& toMovePoints, Vector2D beginPoint)
{
  Vector2D firstToMovePoint = toMovePoints[0];
  float distFirstSegment = Math2::distance(beginPoint.getX(), beginPoint.getY(), firstToMovePoint.getX(), firstToMovePoint.getY());
  m_lengthSegments.push_back(distFirstSegment);

  float curDist(0);
  float totalDist(0);

  totalDist += distFirstSegment;

  for (int i = 0; i < toMovePoints.size() - 1; i++)
  {
    Vector2D point1(toMovePoints[i].getX(), toMovePoints[i].getY());
    Vector2D point2(toMovePoints[i + 1].getX(), toMovePoints[i + 1].getY());

    curDist = Math2::distance(point1.getX(), point1.getY(), point2.getX(), point2.getY());
    totalDist += curDist;

    m_lengthSegments.push_back(curDist);
  }
}

Vector2D JellyFishMover::getVelocity()
{
  return Vector2D();
}

void JellyFishMover::setState(State state)
{
  Mover::setState(state);

  switch (state)
  {
  case State::STOP:


    if (m_indexCurrentPoint < m_toMovePoints.size())
    {
      setNextPoint(m_indexCurrentPoint, m_toMovePoints, m_lengthSegments);

      m_prevDist = Math2::distance(m_endPoint.getX(), m_endPoint.getX(), m_currentPos.getX(), m_currentPos.getY());
      m_maxDist = Math2::distance(m_endPoint.getX(), m_endPoint.getY(), m_beginPoint.getX(), m_beginPoint.getY());

      setNewPosition(m_currentPos);

      setState(State::MOVE);
    }
    else
    {
      Point beginPoint(m_currentPos.getX(), m_currentPos.getY());
      Vector2D nextRandomPoint = m_callbackStopMoveEndPath(beginPoint);

      setEndPoint(nextRandomPoint);
      setBeginPoint(Vector2D(beginPoint.x, beginPoint.y));

      init();
      startMove();
    }

    m_timerEasing = 0;
    break;

  case State::MOVE: 
    break;
  }
}

void JellyFishMover::setNextPoint(int indexPoint, const std::vector<Vector2D>& toMovePoints, const std::vector<float>& lengthSegments)
{
  if (toMovePoints.size() > 0 && lengthSegments.size() > 0)
  {
    if (indexPoint < toMovePoints.size())
    {
      Vector2D endPoint(m_toMovePoints[indexPoint].getX(), m_toMovePoints[indexPoint].getY());
      setEndPoint(endPoint);
      if (indexPoint > 0)
      {
        Vector2D beginPoint(m_toMovePoints[indexPoint - 1].getX(), m_toMovePoints[indexPoint - 1].getY());
        setBeginPoint(beginPoint);
        setCurrentPoint(beginPoint);
      }
    }

    if (indexPoint < lengthSegments.size())
    {
      m_lengthCurrentSegment = m_lengthSegments[indexPoint];
    }
  }
  m_indexCurrentPoint++;
}

