#include "Pickup.h"

void Pickup::onInit()
{
  std::sr1::shared_ptr<Texture> texture = getResources()->load<Texture>("sprites/weapons");
  spriteRenderer = getEntity()->addComponent<SpriteRenderer>(texture);

  std::sr1::shared_ptr<BoxCollider> bc = getEntity()->addComponent<BoxCollider>();
  bc->setSize(Vector3(1, 2, 1));
  bc->setOffset(Vector3(0, -1, 0));

  getTransform()->setScale(Vector3(5, 5, 1));
  getTransform()->setPosition(Vector3(0, 0, -5));
}
