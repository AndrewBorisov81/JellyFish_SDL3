#pragma once

class Vector2D
{
  float m_x{ 0.0f };
  float m_y{ 0.0f };
public:
  Vector2D() {}
  Vector2D(float x, float y) : m_x(x), m_y(y) { }

  float getX() const { return m_x; }
  float getY() const { return m_y; }

  void setX(float x) { m_x = x; }
  void setY(float y) { m_y = y; }

  //finding the length of the vector
  float length();

  //addition of two Vectors using + or +=
  Vector2D operator + (const Vector2D& v2) const;
  friend Vector2D& operator += (Vector2D& v1, const Vector2D& v2);

  //multiplication of a vector with a scalar number using * or *=
  Vector2D operator * (float scalar);
  Vector2D& operator *= (float scalar);

  //subtraction of two vector using - or -=
  Vector2D operator - (const Vector2D& v2) const;
  friend Vector2D& operator -= (Vector2D& v1, const Vector2D& v2);

  //division of a vector by a scalar number using / or /=
  Vector2D operator / (float scalar);
  Vector2D& operator /= (float scalar);

  //normalizing a vector
  void normalize();
  Vector2D getNormalized() const;
  Vector2D& Zero();
  float dot(const Vector2D& v) const;

  //static float angle(const Vector2D& v1, const Vector2D& v2);
  //static float angle(const Vector2D& v);

  //float dot(const Vector2D& v) const;

  float getAngle(const Vector2D& other) const;

  float cross(const Vector2D& other) const;
};

