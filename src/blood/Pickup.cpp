#include "Pickup.h"

void Pickup::onInit()
{
  std::sr1::shared_ptr<Texture> texture = getResources()->load<Texture>("sprites/weapons");
  spriteRenderer = getEntity()->addComponent<SpriteRenderer>(texture);

  getTransform()->setScale(Vector3(5, 5, 1));
}
