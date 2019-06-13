#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
  #include <emscripten.h>
#endif

#include <vector>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

extern "C"
{
  void PlatformInit();
  void PlatformTick();
  void PlatformKeyDown(char key);
  void PlatformKeyUp(char key);
  void PlatformDisplay(int width, int height, int type, unsigned char *buffer);
}

std::vector<unsigned char> buffer;
SDL_Surface* screen;
bool quit;

void emloop()
{
  SDL_Event event = {0};

  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      quit = true;
#ifdef __EMSCRIPTEN__
      abort();
#endif
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

  int width = WIDTH;
  int height = HEIGHT;

  if(buffer.size() < width * height * 3)
  {
    buffer.resize(width * height * 3);
  }

  PlatformDisplay(width, height, 13, &buffer.at(0));
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

  SDL_Flip(screen);
}

int main()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0) abort();

  screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
  if(!screen) abort();

  //try
  //{
    PlatformInit();
  //}
  //catch(std::exception& e)
  //{
  //  std::cout << "Exception: " << e.what() << std::endl;
  //}

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(emloop, 0, 1);
#else
  while(!quit)
  {
    emloop();
  }
#endif

  return 0;
}
