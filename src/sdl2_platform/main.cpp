#include <SDL2/SDL.h>

#include <vector>

#define WIDTH 800
#define HEIGHT 600

extern "C"
{
  void PlatformInit();
  void PlatformTick();
  void PlatformKeyDown(char key);
  void PlatformKeyUp(char key);
  void PlatformDisplay(int width, int height, unsigned char *buffer);
}

std::vector<unsigned char> buffer;

#undef main
int main()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0) abort();

  SDL_Window* window = SDL_CreateWindow("SDL2 Platform",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

  if(!window) abort();

  PlatformInit();

  SDL_Event event = {0};
  bool quit = false;

  while(!quit)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
      else if(event.type == SDL_KEYDOWN)
      {
        PlatformKeyDown(event.key.keysym.sym);
      }
      else if(event.type == SDL_KEYUP)
      {
        PlatformKeyUp(event.key.keysym.sym);
      }
    }

    PlatformTick();

    SDL_Surface* screen = SDL_GetWindowSurface(window);

    int width = 0;
    int height = 0;
    SDL_GetWindowSize(window, &width, &height);

    if(buffer.size() < width * height * 3)
    {
      buffer.resize(width * height * 3);
    }

    PlatformDisplay(width, height, &buffer.at(0));
    unsigned char *p = &buffer.at(0);
    SDL_Rect r = {0};
    r.w = 1;
    r.h = 1;

    for(int y = 0; y < height; y++)
    {
      r.y = y;
      for(int x = 0; x < width; x++)
      {
        r.x = x;

        SDL_FillRect(screen, &r, SDL_MapRGB(screen->format,
          *(p), *(p + 1), *(p + 2)));

        p += 3;
      }
    }

    SDL_UpdateWindowSurface(window);
  }

  return 0;
}
