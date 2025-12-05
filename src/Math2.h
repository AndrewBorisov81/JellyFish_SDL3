#pragma once

#define MATH_TOLERANCE              2e-37f
//# define M_PI           3.14159265358979323846 
#define DBL_TRUE_MIN     4.9406564584124654e-324 // min positive value
#define FLT_EPSILON      1.192092896e-07F        // smallest such that 1.0+FLT_EPSILON != 1.0

#include <math.h>

struct Point;

class Math2
{
public:
  static float area(Point A, Point B, Point C);
  static bool isInside(Point A, Point B, Point C, Point D, Point m);
  static float distance(int x1, int y1, int x2, int y2);
};
