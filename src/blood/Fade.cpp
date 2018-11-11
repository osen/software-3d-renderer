#include "Fade.h"

void Fade::onTick()
{
  if(disable) return;
  Color c(0, 0, 0, amount);

  for(size_t y = 0; y < overlay->getHeight(); y++)
  {
    for(size_t x = 0; x < overlay->getHeight(); x++)
    {
      overlay->setPixel(x, y, c);
    }
  }

  if(fadeIn == true)
  {
    amount -= 100 * getEnvironment()->getDeltaTime();

    if(amount <= 0)
    {
      disable = true;
    }
  }
}

void Fade::onGui()
{
  if(disable) return;
  getGui()->image(Vector2(0, 0), overlay);
}

void Fade::onInit()
{
  overlay = getResources()->create<Texture>(
    getWindow()->getBuffer()->getWidth(),
    getWindow()->getBuffer()->getHeight());

  fadeIn = true;

  if(fadeIn == true)
  {
    amount = 255;
  }
}
