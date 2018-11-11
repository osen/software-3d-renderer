#include "BongoCat.h"

void BongoCat::onInit()
{
  music = getResources()->load<Sound>("sounds/bongo");
  getTransform()->setScale(Vector3(30, 30, 1));
  getTransform()->setPosition(Vector3(0, 10, -25));

  texture = getResources()->load<Texture>("sprites/bongo_cat");
  spriteRenderer = getEntity()->addComponent<SpriteRenderer>(texture);
  spriteRenderer->setLayout(1, 2);
  spriteRenderer->setFrame(0, 0);
}

void BongoCat::onTick()
{
  frame += 4 * getEnvironment()->getDeltaTime();

  if(frame > 2)
  {
    frame = 0;
    getAudio()->playSound(music);
  }

  spriteRenderer->setFrame(0, frame);
}
