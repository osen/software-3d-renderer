#include "Zombie.h"
#include "Player.h"
#include "HitBox.h"

#include <iostream>

#include <cmath>

void Zombie::onInit()
{
  //groan = getResources()->load<Sound>("sounds/dixie_horn");
  groan = getResources()->load<Sound>("sounds/zombie_groan");
  activateGroan = getResources()->load<Sound>("sounds/zombie_activate");
  texture = getResources()->load<Texture>("sprites/zombie");
  getTransform()->setScale(Vector3(2, 3.0f, 1));
  //activate();
}

void Zombie::activate()
{
  //std::cout << "Activating" << std::endl;
  spriteRenderer = getEntity()->addComponent<SpriteRenderer>(texture);
  spriteRenderer->setLayout(9, 3);
  spriteRenderer->setFrame(0, 1);
  state = 1;
  getAudio()->playSound(activateGroan);
}

void Zombie::checkHits()
{
  std::vector<std::shared_ptr<Entity> > entities;

  getWorld()->getEntities<HitBox>(entities);

  for(std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
    it != entities.end(); it++)
  {
    std::shared_ptr<HitBox> hb = (*it)->getComponent<HitBox>();

    //if(hb->getOwner() == getEntity()) continue;
    if(hb->getOwner() != getWorld()->getEntity<Player>()) continue;

    Vector3 diff = getTransform()->getPosition() - (*it)->getTransform()->getPosition();
    float len = fabs(diff.x) + fabs(diff.y) + fabs(diff.z);

    //if(!(*it)->isAlive()) continue;

    if(len < 2)
    {
      getAudio()->playSound(groan);
      (*it)->kill();
      getEntity()->kill();
    }

    return;
  }
}

void Zombie::onTick()
{
  std::shared_ptr<Entity> pe = getWorld()->getEntity<Player>();
  Vector3 diff = getTransform()->getPosition() - pe->getTransform()->getPosition();
  float len = fabs(diff.x) + fabs(diff.y) + fabs(diff.z);

  if(len < 10)
  {
    if(!spriteRenderer)
    {
      activate();
    }
  }

  std::shared_ptr<StaticModelCollider> smc = getWorld()->getEntity<StaticModelCollider>()->getComponent<StaticModelCollider>();

  getTransform()->lookAt(pe->getTransform()->getPosition());

  Vector3 lp = getTransform()->getPosition();

  if(state == 2)
  {
    if(len < 100 && len > 2)
    {
      getTransform()->translate(Vector3(0, 0, 3) * getEnvironment()->getDeltaTime());
    }
  }

  getTransform()->translate(Vector3(0, -4, 0) * getEnvironment()->getDeltaTime());
  Vector3 np = getTransform()->getPosition();

  bool solved = false;
  Vector3 sp = smc->getCollisionResponse(np, Vector3(2, 3, 2), solved, lp);

  if(solved)
  {
    np = sp;
  }
  else
  {
    np = lp;
  }

  getTransform()->setPosition(np);

  if(state == 1)
  {
    frame += 6 * getEnvironment()->getDeltaTime();

    if(frame >= 9)
    {
      frame = 0;
      state = 2;
      spriteRenderer->setFrame(frame, 0);
    }
    else
    {
      spriteRenderer->setFrame(frame, 1);
    }
  }
  else if(state == 2)
  {
    frame += 9 * getEnvironment()->getDeltaTime();
    if(frame >= 6) frame = 0;
    spriteRenderer->setFrame(frame, 0);
    checkHits();

    if(len < 2)
    {
      attack = 0;
      state = 3;
    }
  }
  else if(state == 3)
  {
    float pa = attack;
    spriteRenderer->setFrame(attack, 2);
    attack += 6 * getEnvironment()->getDeltaTime();

    if(pa < 3 && attack >= 3)
    {
      doAttack();
    }

    checkHits();

    if(attack >= 4)
    {
      frame = 0;
      spriteRenderer->setFrame(frame, 0);
      state = 2;
    }
  }
}

void Zombie::doAttack()
{
  std::shared_ptr<Entity> hbe = getWorld()->addEntity();
  hbe->getTransform()->setRotation(getTransform()->getRotation());
  hbe->getTransform()->setPosition(getTransform()->getPosition());
  hbe->getTransform()->translate(Vector3(0, 0, 1));
  hbe->addComponent<HitBox>(getEntity());
}
