
#include "Vector2D.h"
#include "Math2.h"

#include <math.h>
#include <stdlib.h>

float Vector2D::length()
{
  return (float)sqrt((m_x * m_x) + (m_y * m_y));
}

Vector2D Vector2D::operator + (const Vector2D& v2) const
{
  return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D& operator += (Vector2D& v1, const Vector2D& v2)
{
  v1.m_x += v2.m_x;
  v1.m_y += v2.m_y;

  return v1;
}

Vector2D Vector2D::operator * (float scalar)
{
  return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D& Vector2D::operator *= (float scalar)
{
  m_x *= scalar;
  m_y *= scalar;

  return *this;
}

Vector2D Vector2D::operator - (const Vector2D& v2) const
{
  return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

Vector2D& operator -= (Vector2D& v1, const Vector2D& v2)
{
  v1.m_x -= v2.m_x;
  v1.m_y -= v2.m_y;

  return v1;
}

Vector2D Vector2D::operator / (float scalar)
{
  return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& Vector2D::operator /= (float scalar)
{
  m_x /= scalar;
  m_y /= scalar;

  return *this;
}

void Vector2D::normalize()
{
  float n = m_x * m_x + m_y * m_y;
 
  if (n == 1.0f)
    return;

  n = sqrt(n);

  if (n < MATH_TOLERANCE)
    return;

  n = 1.0f / n;
  m_x *= n;
  m_y *= n;
}

Vector2D& Vector2D::Zero()
{
  m_x = 0;
  m_y = 0;

  return *this;
}

Vector2D Vector2D::getNormalized() const
{
  Vector2D v(*this);
  v.normalize();
  return v;
}

float Vector2D::getAngle(const Vector2D& other) const
{
  Vector2D a2 = getNormalized();
  Vector2D b2 = other.getNormalized();
  float angle = atan2f(a2.cross(b2), a2.dot(b2));
  if (fabs(angle) < FLT_EPSILON) return 0.f;
  return angle;
}

float Vector2D::dot(const Vector2D& v) const
{
  return (m_x * v.getX() + m_y * v.getY());
}

float Vector2D::cross(const Vector2D& other) const {
  return m_x * other.getY() - m_y * other.getX();
}

/*float Vector2D::angle(const Vector2D& v)
{
  float angle = atan2(v.getY(), v.getX()) * 180 / M_PI;
  return angle;
}*/

/*float Vector2D::angle(const Vector2D& v1, const Vector2D& v2)
{
  bool rotClockwise = true;
  float angle = 0;
  angle = atan2(v2.getY() - v1.getY(), v2.getX() - v1.getX()) * 180 / M_PI;
  return angle;
}*/

