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

void platform_main(std::shared_ptr<Platform> platform);

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
  rtn->environment = Environment::initialize();

  platform_main(rtn);

  return rtn;
}

void Platform::keyDown(char key)
{
  keyboard->keys.push_back(key);
  keyboard->pressedKeys.push_back(key);
}

void Platform::keyUp(char key)
{
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

void Platform::tick()
{
  audio->tick();
  environment->tick();
  world->tick();

  keyboard->pressedKeys.clear();
}

void drawBlock(unsigned char *src, int width, int height,
  qsoft::Vector4& r, qsoft::Color& c)
{
  int rx = r.x;
  int ry = r.y;
  int rw = r.z;
  int rh = r.w;

  for(int y = 0; y < rh; y++)
  {
    if(ry + y >= height) break;

    unsigned char *yp = src + width * 3 * (ry + y);
    unsigned char *xp = yp + rx * 3;

    for(int x = 0; x < rw; x++)
    {
      if(rx + x >= width) break;
      *(xp) = c.r;
      *(xp + 1) = c.g;
      *(xp + 2) = c.b;
      xp += 3;
    }
  }
}

void Platform::display(int width, int height, int type, unsigned char *buffer)
{
  window->width = width;
  window->height = height;

  //getWindow()->getShadow()->setRaw(buffer, width, height, type);

  std::shared_ptr<qsoft::Texture> b = window->buffer;
  b->clear();
  b->setRaw(buffer, width, height, type);

  world->display();
  world->gui();

/*
  double zx = window->width / 320.0f;
  double zy = window->height / 240.0f;
  qsoft::Color c;
  qsoft::Vector4 r;

  for(int y = 0; y < b->getHeight(); y++)
  {
    for(int x = 0; x < b->getWidth(); x++)
    {
      c = b->getPixel(x, y);
      r.x = x * zx;
      r.y = y * zy;
      r.z = zx + 1;
      r.w = zy + 1;
      drawBlock(buffer, window->width, window->height, r, c);
    }
  }
*/
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

std::sr1::shared_ptr<Gui> Platform::getGui()
{
  return gui;
}

std::sr1::shared_ptr<Audio> Platform::getAudio()
{
  return audio;
}
