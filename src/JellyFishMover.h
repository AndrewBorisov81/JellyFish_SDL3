#pragma once

#include "Mover.h"
#include <vector>
#include <cstdint>

class Vector2D;
class Size;

class JellyFishMover : public Mover
{
public:
  JellyFishMover();
  JellyFishMover(Vector2D endPoint);
  ~JellyFishMover() override;

  bool init() override;

  void update() override;
  void move() override;

  void tick();

  void startMove() override;
  void stopMove() override;

  void setObjectSize(Size objectSize) override;

  void calculateToMovePoints(std::vector<Vector2D>& toMovePoints, Vector2D beginPoint, Vector2D endPoint, float objectLength);
  void calculateLengthSegments(std::vector<float>& m_lengthSegments, const std::vector<Vector2D>& toMovePoints, Vector2D beginPoint);

  Vector2D getVelocity();

  void setState(State aState) override;

  void setNextPoint(int indexPoint, const std::vector<Vector2D>& toMovePoints, const std::vector<float>& m_lengthSegments);

private:
  std::vector<Vector2D> m_toMovePoints;
  std::vector<float> m_lengthSegments;

  int m_indexCurrentPoint{ 0 };
  float m_lengthCurrentSegment{ 0.0f };

  float m_objectMaxLength{ 0.0f };

  Vector2D m_moveDirection{ 0, 0 };

  Vector2D m_prevCurrentPos{ 0.0f, 0.0f };
  Vector2D m_newCurrentPos{ 0.0f, 0.0f };

  Vector2D m_newPos{ 0.0f, 0.0f };
  float m_timerEasing{ 0.0f };
  float m_maxDist{ 0.0f };
  float m_deltaShiftPath{ 0.0f };

  unsigned int last_tick_time{ 0 };
  float delta{ 0.0f };
};

