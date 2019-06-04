#include "Player.h"
#include "HitBox.h"
#include "GameScreen.h"
#include "BongoScreen.h"
#include "Fade.h"

#include <cmath>

void Player::onInit()
{
  speed = 4;
  model = getResources()->load<Model>("models/curuthers/curuthers");
  pitchfork = getResources()->load<Texture>("sprites/pitchfork");
  heart = getResources()->load<Texture>("sprites/heart");
  health = 100;

  getEntity()->addComponent<Camera>();
  //getEntity()->addComponent<Fade>();

  std::shared_ptr<BoxCollider> bc = getEntity()->addComponent<BoxCollider>();
  bc->setSize(Vector3(1, 2, 1));
  bc->setOffset(Vector3(0, -1, 0));
}

void Player::doAttack()
{
  //std::cout << "Attack" << std::endl;
  std::shared_ptr<Entity> hbe = getWorld()->addEntity();
  hbe->getTransform()->setRotation(getTransform()->getRotation());
  hbe->getTransform()->setPosition(getTransform()->getPosition());
  hbe->getTransform()->translate(Vector3(0, 0, 1));
  hbe->addComponent<HitBox>(getEntity());
}

void Player::checkHits()
{
  std::vector<std::shared_ptr<Entity> > entities;

  getWorld()->getEntities<HitBox>(entities);

  for(std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
    it != entities.end(); it++)
  {
    std::shared_ptr<HitBox> hb = (*it)->getComponent<HitBox>();

    if(hb->getOwner() == getEntity()) continue;

    Vector3 diff = getTransform()->getPosition() - (*it)->getTransform()->getPosition();
    float len = fabs(diff.x) + fabs(diff.y) + fabs(diff.z);

    if(len > 2) continue;

    health -= 25;

    if(health < 0) health = 0;

    if(health <= 0)
    {
      getWorld()->reset();
      getWorld()->addEntity<GameScreen>();
    }

    diff = diff * -1;
    diff.y = 0.5f;
    getTransform()->translate(diff);
    return;
  }
}

void Player::onTick()
{
  // Simulate gravity
  getTransform()->translate(Vector3(0, -4, 0) * getEnvironment()->getDeltaTime());

  if(getKeyboard()->isKeyPressed(KEY_T))
  {
    getWorld()->reset();
    getWorld()->addEntity<GameScreen>();
  }
  else if(getKeyboard()->isKeyPressed(KEY_Y))
  {
    getWorld()->reset();
    getWorld()->addEntity<BongoScreen>();
  }

  if(getKeyboard()->isKeyDown(KEY_LEFT))
  {
    getTransform()->setRotation(
      getTransform()->getRotation() + Vector3(0, 90, 0) * getEnvironment()->getDeltaTime());
  }
  else if(getKeyboard()->isKeyDown(KEY_RIGHT))
  {
    getTransform()->setRotation(
      getTransform()->getRotation() + Vector3(0, -90, 0) * getEnvironment()->getDeltaTime());
  }

  if(getKeyboard()->isKeyDown(KEY_UP))
  {
    getTransform()->translate(Vector3(0, 0, speed) * getEnvironment()->getDeltaTime());
  }
  else if(getKeyboard()->isKeyDown(KEY_DOWN))
  {
    getTransform()->translate(Vector3(0, 0, -speed) * getEnvironment()->getDeltaTime());
  }

  if(getKeyboard()->isKeyDown(KEY_SPACE))
  {
    if(attack == 0)
    {
      attack = 0.01f;
    }
  }

  if(attack > 0)
  {
    float la = attack;
    attack += 6 * getEnvironment()->getDeltaTime();

    if(la < 2 && attack >= 2)
    {
      doAttack();
    }
  }

  if(attack >= 3) attack = 0;

  checkHits();
}

void Player::onGui()
{
  Vector4 clip = Vector4(0, 0, pitchfork->getWidth() / 3, pitchfork->getHeight());

  clip.x = clip.z * (int)attack;
  //std::cout << clip.x << std::endl;

  float idealSize = getWindow()->getHeight() / 3.0f;

  Vector4 wpos(0, 0, idealSize, 0);
  wpos.w = (idealSize / clip.z) * clip.w;
  wpos.x = getWindow()->getWidth() / 2.0f - wpos.z / 2.0f;
  wpos.y = getWindow()->getHeight() - wpos.w;

  //std::cout << wpos.z / clip.z << std::endl;

  getGui()->image(wpos, pitchfork, clip);

  for(int i = 0; i < 4; i++)
  {
    if(health <= i * 25) break;

    clip = Vector4(0, 0, heart->getWidth() * 3, heart->getHeight() * 3);
    clip.x = 10 + i * clip.z;
    clip.y = getWindow()->getHeight() - 10 - clip.w;

    getGui()->image(clip, heart);
  }
}

