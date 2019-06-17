#include "HitBox.h"

void HitBox::onInit(std::sr1::shared_ptr<Entity> owner)
{
  this->owner = owner;

  //std::sr1::shared_ptr<SpriteRenderer> sr = getEntity()->addComponent<SpriteRenderer>();
  //sr->setTexture(getResources()->load<Texture>("sprites/zombie"));

  timeout = 0.5f;
}

void HitBox::onTick()
{
  if(timeout <= 0)
  {
    getEntity()->kill();
  }

  //timeout -= getEnvironment()->getDeltaTime();
  timeout -= 1;
}

std::sr1::shared_ptr<Entity> HitBox::getOwner()
{
  return owner.lock();
}
