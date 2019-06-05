#include "Platform.h"

#include <memory>

std::shared_ptr<Platform> p;

extern "C"
{

void PlatformInit()
{
  p = Platform::initialize();
}

void PlatformTick()
{
  p->tick();
}

void PlatformKeyDown(char key)
{
  p->keyDown(key);
}

void PlatformKeyUp(char key)
{
  p->keyUp(key);
}

void PlatformDisplay(int width, int height, unsigned char *buffer)
{
  p->display(width, height, buffer);
}

}
