#include "Vertex.h"
#include "Matrix.h"
#include "Util.h"

// TODO:
#include <exception>

namespace qsoft
{

Vertex Vertex::transform(Matrix& m) const
{
  Vertex v;

  v.position = m * position;
  v.texCoord = texCoord;

  return v;
}

float Vertex::getComponent(int index) const
{
  if(index == 0) return position.x;
  else if(index == 1) return position.y;
  else if(index == 2) return position.z;
  else if(index == 3) return position.w;
  // TODO
  throw std::exception();
}

Vertex Vertex::lerp(const Vertex& a, const Vertex& b, float amt)
{
  Vertex r;

  r.position.x = Util::lerp(a.position.x, b.position.x, amt);
  r.position.y = Util::lerp(a.position.y, b.position.y, amt);
  r.position.z = Util::lerp(a.position.z, b.position.z, amt);
  r.position.w = Util::lerp(a.position.w, b.position.w, amt);
  r.texCoord.x = Util::lerp(a.texCoord.x, b.texCoord.x, amt);
  r.texCoord.y = Util::lerp(a.texCoord.y, b.texCoord.y, amt);
  // TODO
  //r.normal.x = Util::lerp(a.normal.x, b.normal.x, amt);
  //r.normal.y = Util::lerp(a.normal.y, b.normal.y, amt);
  //r.normal.z = Util::lerp(a.normal.z, b.normal.z, amt);

  return r;
}

}
