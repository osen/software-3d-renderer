#ifndef QSOFT_VERTEX_H
#define QSOFT_VERTEX_H

#include "Vector.h"

namespace qsoft
{

struct Matrix;

struct Vertex
{
  // TODO: Simplify to Vector3
  Vector4 position;
  Vector2 texCoord;

  static Vertex lerp(const Vertex& a, const Vertex& b, float amt);
  Vertex transform(Matrix& m) const;
  float getComponent(int index) const;
};

}

#endif
