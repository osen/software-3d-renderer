#ifndef QPLATFORM_COMPONENT_H
#define QPLATFORM_COMPONENT_H

#include <sr1/noncopyable>
#include <sr1/memory>

class Platform;
class Environment;
class Window;
class Keyboard;
class Entity;
class Resources;
class World;
class Transform;
class Gui;
class Audio;

class Component : public std::sr1::noncopyable
{
  friend class Entity; // to call init() during construction.

public:
  std::sr1::shared_ptr<Platform> getPlatform();
  std::sr1::shared_ptr<World> getWorld();
  std::sr1::shared_ptr<Environment> getEnvironment();
  std::sr1::shared_ptr<Window> getWindow();
  std::sr1::shared_ptr<Keyboard> getKeyboard();
  std::sr1::shared_ptr<Resources> getResources();
  std::sr1::shared_ptr<Entity> getEntity();
  std::sr1::shared_ptr<Transform> getTransform();
  std::sr1::shared_ptr<Gui> getGui();
  std::sr1::shared_ptr<Audio> getAudio();

private:
  virtual void onInit();
  virtual void onBegin();
  virtual void onTick();
  virtual void onDisplay();
  virtual void onGui();

  //void init();
  void begin();
  void tick();
  void display();
  void gui();

  std::sr1::weak_ptr<Platform> platform;
  std::sr1::weak_ptr<Entity> entity;

};

#endif
