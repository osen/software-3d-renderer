#include "Mesh.h"
#include "Face.h"

#include <vector>

namespace qsoft
{

struct MeshImpl
{
  std::vector<Face> faces;
};

Mesh::Mesh() : impl(std::sr1::make_shared<MeshImpl>())
{

}

std::vector<Face>& Mesh::getFaces()
{
  return impl->faces;
}

void Mesh::addFace(Face& face)
{
  impl->faces.push_back(face);
}

}
