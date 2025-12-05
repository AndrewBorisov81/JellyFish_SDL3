#include "Easing.h"

float Easing::easeInOutQuad(float t)
{
    t *= 2;
    if (t < 1) return 0.5f * t * t;

    t -= 1;
    return -0.5f * ((t)*(t - 2) - 1);
}

float Easing::easeOutQuad(float t)
{
  return t * (2 - t);
}
