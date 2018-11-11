#ifndef QPLATFORM_ENTITY_H
#define QPLATFORM_ENTITY_H

#include "Exception.h"

#include <sr1/noncopyable>
#include <sr1/zero_initialized>

#include <memory>
#include <vector>

class Component;
class Platform;
class Transform;

#define ENTITY_ADDCOMPONENT \
  std::shared_ptr<T> rtn = std::make_shared<T>(); \
  rtn->entity = self; \
  rtn->platform = platform; \
  components.push_back(rtn);

class Entity : public std::sr1::noncopyable
{
  friend class World; // for tick(), platform

public:
  //void destroy();
  //bool isDestroyed();
  bool isAlive();

  template <typename T>
  std::shared_ptr<T> addComponent()
  {
    ENTITY_ADDCOMPONENT
    rtn->onInit();

    return rtn;
  }

  template <typename T, typename A>
  std::shared_ptr<T> addComponent(A a)
  {
    ENTITY_ADDCOMPONENT
    rtn->onInit(a);

    return rtn;
  }

  template<typename T>
  bool hasComponent()
  {
    for(std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
      it != components.end(); it++)
    {
      std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(*it);

      if(t)
      {
        return true;
      }
    }

    return false;
  }

  template<typename T>
  std::shared_ptr<T> getComponent()
  {
    for(std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
      it != components.end(); it++)
    {
      std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(*it);

      if(t)
      {
        return t;
      }
    }

    throw Exception("Failed to obtain component");
  }

  std::shared_ptr<Transform> getTransform();
  void kill();

private:
  void tick();
  void display();
  void gui();

  std::weak_ptr<Platform> platform;
  std::weak_ptr<Entity> self;
  std::vector<std::shared_ptr<Component> > components;
  std::sr1::zero_initialized<bool> alive;

};

#endif
