#include "Environment.h"

#include <SDL2/SDL.h>

float Environment::getDeltaTime()
{
  return deltaTime;
}

std::string Environment::getDataPath()
{
  return "data";
}

std::shared_ptr<Environment> Environment::initialize()
{
  std::shared_ptr<Environment> rtn = std::make_shared<Environment>();

  rtn->lastTime = SDL_GetTicks();

  return rtn;
}

void Environment::tick()
{
  double now = SDL_GetTicks();
  double diffTime = now - lastTime;
  lastTime = now;
  deltaTime = diffTime / 1000.0f;

  if(deltaTime > 0.5f) deltaTime = 0.5f;
}
