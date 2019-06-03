#include "Component.h"
#include "Platform.h"
#include "Entity.h"
#include "Transform.h"

void Component::onInit() { }
void Component::onBegin() { }
void Component::onTick() { }
void Component::onDisplay() { }
void Component::onGui() { }

/*
void Component::init()
{
  onInit();
}
*/

void Component::begin()
{
  onBegin();
}

void Component::tick()
{
  onTick();
}

void Component::display()
{
  onDisplay();
}

void Component::gui()
{
  onGui();
}

std::shared_ptr<Platform> Component::getPlatform()
{
  return platform.lock();
}

std::shared_ptr<Window> Component::getWindow()
{
  return getPlatform()->getWindow();
}

std::shared_ptr<World> Component::getWorld()
{
  return getPlatform()->getWorld();
}

std::shared_ptr<Resources> Component::getResources()
{
  return getPlatform()->getResources();
}

std::shared_ptr<Environment> Component::getEnvironment()
{
  return getPlatform()->getEnvironment();
}

std::sr1::shared_ptr<Gui> Component::getGui()
{
  return getPlatform()->getGui();
}

std::shared_ptr<Keyboard> Component::getKeyboard()
{
  return getPlatform()->getKeyboard();
}

std::sr1::shared_ptr<Audio> Component::getAudio()
{
  return getPlatform()->getAudio();
}

std::shared_ptr<Entity> Component::getEntity()
{
  return entity.lock();
}

std::shared_ptr<Transform> Component::getTransform()
{
  return getEntity()->getComponent<Transform>();
}
