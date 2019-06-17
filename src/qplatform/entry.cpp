#include "Platform.h"

#include <memory>

std::sr1::shared_ptr<Platform> p;

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

void PlatformDisplay(int width, int height, int type, unsigned char *buffer)
{
  p->display(width, height, type, buffer);
}

}
