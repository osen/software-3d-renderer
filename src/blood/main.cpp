#include "GameScreen.h"

#include <qplatform/qplatform.h>

int main()
{
  std::shared_ptr<Platform> p = Platform::initialize();

  std::shared_ptr<Entity> e = p->getWorld()->addEntity();
  std::shared_ptr<GameScreen> ms = e->addComponent<GameScreen>();

  p->run();

  return 0;
}

