#include "BongoScreen.h"
#include "Player.h"
#include "Zombie.h"
#include "BongoCat.h"

#include <iostream>

void BongoScreen::onInit()
{
  std::shared_ptr<Model> model = getResources()->load<Model>("models/bongo/bongo");
  getEntity()->addComponent<ModelRenderer>(model);
  std::shared_ptr<StaticModelCollider> smc = getEntity()->addComponent<StaticModelCollider>();

  std::shared_ptr<Entity> player = getWorld()->addEntity<Player>();
  player->getComponent<Transform>()->setPosition(Vector3(-4, 3, 0));
  player->getComponent<Transform>()->setRotation(Vector3(0, -90, 0));

  getWorld()->addEntity<BongoCat>();

  timeout = 10;
}

void BongoScreen::onTick()
{
  timeout -= getEnvironment()->getDeltaTime();

  if(timeout <= 0)
  {
    std::cout << "Timeout reached" << std::endl;

    for(size_t i = 0; i < 5; i++)
    {
      addZombie();
    }

    timeout = 5;
  }
}

float BongoScreen::generateRandom()
{
  int r = rand();

  return (float) r / (float)RAND_MAX;
}

void BongoScreen::addZombie()
{
  std::shared_ptr<Entity> e = getWorld()->addEntity();
  //e->getComponent<Transform>()->setPosition(position);
  float x = generateRandom();
  float y = generateRandom();

  x *= 25;
  y *= 25;

  std::cout << "Zombie Spawn: " << x << " " << y << std::endl;

  e->getComponent<Transform>()->setPosition(Vector3(x, 3, y));
  std::shared_ptr<Zombie> sr = e->addComponent<Zombie>();
  sr->activate();
}
