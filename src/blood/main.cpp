#include "GameScreen.h"

#include <qplatform/qplatform.h>

void platform_main(std::shared_ptr<Platform> platform)
{
  std::shared_ptr<Entity> e = platform->getWorld()->addEntity();
  std::shared_ptr<GameScreen> ms = e->addComponent<GameScreen>();
}

