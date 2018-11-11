#include <SDL2/SDL.h>

#include <sr1/noncopyable>
#include <sr1/zero_initialized>

#include <memory>

class World;
class Environment;
class Keyboard;
class Window;
class Resources;
class Gui;
class Audio;

class Platform : public std::sr1::noncopyable
{
  std::shared_ptr<World> world;
  std::shared_ptr<Resources> resources;
  std::shared_ptr<Environment> environment;
  std::shared_ptr<Keyboard> keyboard;
  std::shared_ptr<Gui> gui;
  std::shared_ptr<Audio> audio;
  std::weak_ptr<Platform> self;
  std::shared_ptr<Window> window;
  std::sr1::zero_initialized<SDL_Window *> _window;
  std::sr1::zero_initialized<bool> quit;

public:
  static std::shared_ptr<Platform> initialize();

  void run();

  std::shared_ptr<World> getWorld();
  std::shared_ptr<Environment> getEnvironment();
  std::shared_ptr<Keyboard> getKeyboard();
  std::shared_ptr<Window> getWindow();
  std::shared_ptr<Resources> getResources();
  std::shared_ptr<Gui> getGui();
  std::shared_ptr<Audio> getAudio();

};
