#include "MaterialGroup.h"

void MaterialGroup::addFace(qsoft::Face& f)
{
  mesh.addFace(f);
}

void MaterialGroup::setTexture(std::shared_ptr<Texture> texture)
{
  this->texture = texture;
}
