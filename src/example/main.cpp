#include <qsoft/qsoft.h>

#include <SDL2/SDL.h>

#include <iostream>

#define WIDTH 800
#define HEIGHT 600

#undef main

int main()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0) abort();
  SDL_Window* window = SDL_CreateWindow("QSoft - Software Renderer",
    100, 100, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

  if(!window) abort();
  SDL_Surface* screen = SDL_GetWindowSurface(window);

  qsoft::Texture b(320, 240);
  qsoft::Texture t(2, 2);
  qsoft::Renderer r;
  qsoft::Mesh m;

  qsoft::Face f;
  f.a.position = qsoft::Vector3(0, 0, 0);
  f.a.texCoord = qsoft::Vector2(0, 0);
  f.b.position = qsoft::Vector3(0, 1, 0);
  f.b.texCoord = qsoft::Vector2(0, 1);
  f.c.position = qsoft::Vector3(1, 1, 0);
  f.c.texCoord = qsoft::Vector2(1, 1);
  m.addFace(f);
  f.a.position = qsoft::Vector3(0, 0, 0);
  f.a.texCoord = qsoft::Vector2(0, 0);
  f.b.position = qsoft::Vector3(1, 0, 0);
  f.b.texCoord = qsoft::Vector2(1, 0);
  f.c.position = qsoft::Vector3(1, 1, 0);
  f.c.texCoord = qsoft::Vector2(1, 1);
  m.addFace(f);

  t.setPixel(0, 0, qsoft::Color(255, 0, 255));
  t.setPixel(1, 0, qsoft::Color(0, 255, 0));
  t.setPixel(0, 1, qsoft::Color(0, 0, 255));
  t.setPixel(1, 1, qsoft::Color(255, 0, 0));

  r.setTarget(b);
  r.setMesh(m);
  r.setTexture(t);

  r.setProjection(qsoft::Matrix::perspective(70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 100.0f));

  SDL_Event event = {0};
  bool quit = false;
  float pos = 0;

  while(!quit)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
      else if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
      {
        screen = SDL_GetWindowSurface(window);
      }
    }

    pos += 0.01f;

    b.clear();

    r.setView(
      //qsoft::Matrix::rotation(qsoft::Vector3(0, 1, 0), pos * 10)
      qsoft::Matrix::translation(qsoft::Vector3(0, 0, 5))
    );

    r.setModel(
      qsoft::Matrix::translation(qsoft::Vector3(0, pos * 0.1f, 0)) *
      qsoft::Matrix::rotation(qsoft::Vector3(-pos, -pos * 100, -pos))
      //qsoft::Matrix::rotation(qsoft::Vector3(0, pos, 0))
      //qsoft::Matrix::rotation(qsoft::Vector3(0, 1, 0), pos)
    );

    r.render();

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));

    for(int y = 0; y < b.getHeight(); y++)
    {
      for(int x = 0; x < b.getWidth(); x++)
      {
        qsoft::Color c = b.getPixel(x, y);
        if(c.a == 0) continue;
        SDL_Rect r;
        r.x = x * 2;
        r.y = y * 2;
        r.w = 2;
        r.h = 2;
        SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, c.r, c.g, c.b));
      }
    }

    SDL_UpdateWindowSurface(window);
  }

  return 0;
}
