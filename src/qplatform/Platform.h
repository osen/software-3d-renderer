#ifndef QPLATFORM_PLATFORM_H
#define QPLATFORM_PLATFORM_H

#include <sr1/noncopyable>
#include <sr1/zero_initialized>
#include <sr1/memory>

#include <vector>

class World;
class Environment;
class Keyboard;
class Window;
class Resources;
class Gui;
class Audio;

class Platform : public std::sr1::noncopyable
{
  std::sr1::shared_ptr<World> world;
  std::sr1::shared_ptr<Resources> resources;
  std::sr1::shared_ptr<Environment> environment;
  std::sr1::shared_ptr<Keyboard> keyboard;
  std::sr1::shared_ptr<Gui> gui;
  std::sr1::shared_ptr<Audio> audio;
  std::sr1::weak_ptr<Platform> self;
  std::sr1::shared_ptr<Window> window;
  std::sr1::zero_initialized<bool> quit;

public:
  static std::sr1::shared_ptr<Platform> initialize();
  void tick();
  void keyDown(char key);
  void keyUp(char key);
  void display(int width, int height, int type, unsigned char *buffer);

  void run();

  std::sr1::shared_ptr<World> getWorld();
  std::sr1::shared_ptr<Environment> getEnvironment();
  std::sr1::shared_ptr<Keyboard> getKeyboard();
  std::sr1::shared_ptr<Window> getWindow();
  std::sr1::shared_ptr<Resources> getResources();
  std::sr1::shared_ptr<Gui> getGui();
  std::sr1::shared_ptr<Audio> getAudio();

};

#endif
