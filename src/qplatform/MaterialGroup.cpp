#include "MaterialGroup.h"

void MaterialGroup::addFace(qsoft::Face& f)
{
  mesh.addFace(f);
}

void MaterialGroup::setTexture(std::sr1::shared_ptr<Texture> texture)
{
  this->texture = texture;
}
