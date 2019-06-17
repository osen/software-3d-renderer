#include "Environment.h"

//#include <SDL2/SDL.h>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <sys/time.h>
#endif

float Environment::getDeltaTime()
{
  return deltaTime;
}

std::string Environment::getDataPath()
{
  return "data";
}

std::sr1::shared_ptr<Environment> Environment::initialize()
{
  std::sr1::shared_ptr<Environment> rtn = std::sr1::make_shared<Environment>();

  //rtn->lastTime = SDL_GetTicks();

#ifdef _WIN32
  FILETIME ft = {0};
  GetSystemTimeAsFileTime(&ft);
  SYSTEMTIME st = {0};
  FileTimeToSystemTime(&ft, &st);
  rtn->lastTime = st.wSecond * 1000 + st.wMilliseconds;
#else
  timeval tp = {0};
  gettimeofday(&tp, NULL);
  rtn->lastTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;
#endif

  return rtn;
}

void Environment::tick()
{
  //double now = SDL_GetTicks();

#ifdef _WIN32
  FILETIME ft = {0};
  GetSystemTimeAsFileTime(&ft);
  SYSTEMTIME st = {0};
  FileTimeToSystemTime(&ft, &st);
  double now = st.wSecond * 1000 + st.wMilliseconds;
#else
  timeval tp = {0};
  gettimeofday(&tp, NULL);
  double now = tp.tv_sec * 1000 + tp.tv_usec / 1000;
#endif
  double diffTime = now - lastTime;
  lastTime = now;
  deltaTime = diffTime / 1000.0f;

  if(deltaTime <= 0) deltaTime = 0.001f;
  if(deltaTime > 0.5f) deltaTime = 0.5f;
}
