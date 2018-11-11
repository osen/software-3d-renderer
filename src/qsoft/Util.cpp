#include "Util.h"

#define M_PI 3.14f

namespace qsoft
{

float Util::degToRad(float input)
{
  return input * M_PI / 180.0f;
}

float Util::lerp(float a, float b, float t)
{
  return (1.0f - t) * a + b * t;
}

}
