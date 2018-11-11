#include "Keyboard.h"

bool Keyboard::isKeyDown(double key)
{
  for(std::vector<double>::iterator kit = keys.begin();
    kit != keys.end(); kit++)
  {
    if(*kit == key)
    {
      return true;
    }
  }

  return false;
}

bool Keyboard::isKeyPressed(double key)
{
  for(std::vector<double>::iterator kit = pressedKeys.begin();
    kit != pressedKeys.end(); kit++)
  {
    if(*kit == key)
    {
      kit = pressedKeys.erase(kit);
      return true;
    }
  }

  return false;
}
