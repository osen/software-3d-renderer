#include "GameScreen.h"
#include "Player.h"
#include "SkyBox.h"
#include "Zombie.h"
#include "Pickup.h"

void GameScreen::onInit()
{
  model = getResources()->load<Model>("models/bl1/bl1");
  modelRenderer = getEntity()->addComponent<ModelRenderer>(model);
  smc = getEntity()->addComponent<StaticModelCollider>();

  std::sr1::shared_ptr<Entity> player = getWorld()->addEntity<Player>();
  player->getComponent<Transform>()->setPosition(Vector3(-4, 4, 0));
  player->getComponent<Transform>()->setRotation(Vector3(0, -90, 0));

  std::sr1::shared_ptr<Entity> skyBox = getWorld()->addEntity<SkyBox>();

  //addSprite("sprites/weapons", Vector3(0, 2, 0));

  addZombie(Vector3(12, 3, -32));
  addZombie(Vector3(12, 3, -50));
  addZombie(Vector3(0, 3, -50));

  std::sr1::shared_ptr<Entity> e = getWorld()->addEntity();
  e->getComponent<Transform>()->setPosition(Vector3(-4, 4, 0));
  std::sr1::shared_ptr<Pickup> p = e->addComponent<Pickup>();
}

void GameScreen::addZombie(Vector3 position)
{
  std::sr1::shared_ptr<Entity> e = getWorld()->addEntity();
  e->getComponent<Transform>()->setPosition(position);
  std::sr1::shared_ptr<Zombie> sr = e->addComponent<Zombie>();
}

void GameScreen::addSprite(std::string path, Vector3 position)
{
  std::sr1::shared_ptr<Entity> e = getWorld()->addEntity();
  e->getComponent<Transform>()->setPosition(position);
  std::sr1::shared_ptr<SpriteRenderer> sr = e->addComponent<SpriteRenderer>();
  sr->setLayout(10, 10);
  sr->setTexture(getResources()->load<Texture>(path));
}
