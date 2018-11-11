#include "Platform.h"
#include "World.h"
#include "Resources.h"
#include "Window.h"
#include "Exception.h"
#include "config.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Gui.h"
#include "Audio.h"

std::shared_ptr<Platform> Platform::initialize()
{
  std::shared_ptr<Platform> rtn = std::make_shared<Platform>();

  rtn->self = rtn;
  rtn->world = World::initialize(rtn);
  rtn->resources = Resources::initialize(rtn);
  rtn->window = Window::initialize();
  rtn->keyboard = std::make_shared<Keyboard>();
  rtn->gui = Gui::initialize(rtn);
  rtn->audio = Audio::initialize(rtn);

  rtn->_window = SDL_CreateWindow(DEFAULT_WINDOW_TITLE,
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    rtn->window->getWidth(), rtn->window->getHeight(),
    SDL_WINDOW_RESIZABLE);

  if(!rtn->window)
  {
    throw Exception("Failed to initialize window");
  }

  rtn->environment = Environment::initialize();

  return rtn;
}

void Platform::run()
{
  quit = false;

  while(!quit)
  {
    SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
      else if(event.type == SDL_KEYDOWN)
      {
        double key = event.key.keysym.sym;
        keyboard->keys.push_back(key);
        keyboard->pressedKeys.push_back(key);
      }
      else if(event.type == SDL_KEYUP)
      {
        double key = event.key.keysym.sym;

        for(std::vector<double>::iterator kit = keyboard->keys.begin();
          kit != keyboard->keys.end();)
        {
          if(*kit == key)
          {
            kit = keyboard->keys.erase(kit);
          }
          else
          {
            kit++;
          }
        }
      }
    }

    audio->tick();
    environment->tick();
    world->tick();

    keyboard->pressedKeys.clear();

    SDL_GetWindowSize(_window, &window->width.data(), &window->height.data());
    SDL_Surface* screen = SDL_GetWindowSurface(_window);
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));
    std::shared_ptr<qsoft::Texture> b = window->buffer;
    b->clear();

    world->display();
    world->gui();

    double zx = window->width / 320.0f;
    double zy = window->height / 240.0f;
    //double zx = window->width / 640.0f;
    //double zy = window->height / 480.0f;

    for(int y = 0; y < b->getHeight(); y++)
    {
      for(int x = 0; x < b->getWidth(); x++)
      {
        qsoft::Color c = b->getPixel(x, y);
        SDL_Rect r;
        r.x = x * zx;
        r.y = y * zy;
        r.w = zx + 1;
        r.h = zy + 1;
        SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, c.r, c.g, c.b));
      }
    }

    SDL_UpdateWindowSurface(_window);
  }
}

std::shared_ptr<Window> Platform::getWindow()
{
  return window;
}

std::shared_ptr<World> Platform::getWorld()
{
  return world;
}

std::shared_ptr<Keyboard> Platform::getKeyboard()
{
  return keyboard;
}

std::shared_ptr<Resources> Platform::getResources()
{
  return resources;
}

std::shared_ptr<Environment> Platform::getEnvironment()
{
  return environment;
}

std::shared_ptr<Gui> Platform::getGui()
{
  return gui;
}

std::shared_ptr<Audio> Platform::getAudio()
{
  return audio;
}
