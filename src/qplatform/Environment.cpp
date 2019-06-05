#include "Environment.h"

//#include <SDL2/SDL.h>
#include <sys/time.h>

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

  //rtn->lastTime = SDL_GetTicks();

  timeval tp = {0};
  gettimeofday(&tp, NULL);
  rtn->lastTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;

  return rtn;
}

void Environment::tick()
{
  //double now = SDL_GetTicks();

  timeval tp = {0};
  gettimeofday(&tp, NULL);
  double now = tp.tv_sec * 1000 + tp.tv_usec / 1000;
  double diffTime = now - lastTime;
  lastTime = now;
  deltaTime = diffTime / 1000.0f;

  if(deltaTime > 0.5f) deltaTime = 0.5f;
}
