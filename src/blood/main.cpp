#include "GameScreen.h"

#include <qplatform/qplatform.h>

void platform_main(std::sr1::shared_ptr<Platform> platform)
{
  std::sr1::shared_ptr<Entity> e = platform->getWorld()->addEntity();
  std::sr1::shared_ptr<GameScreen> ms = e->addComponent<GameScreen>();
}

