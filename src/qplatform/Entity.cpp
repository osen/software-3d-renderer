#include "Entity.h"
#include "Component.h"
#include "Transform.h"

void Entity::tick()
{
/*
  for(std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
    it != components.end(); it++)
  {
    (*it)->tick();
  }
*/

  for(size_t i = 0; i < components.size(); i++)
  {
    components.at(i)->tick();
  }
}

void Entity::display()
{
  for(std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
    it != components.end(); it++)
  {
    (*it)->display();
  }
}

void Entity::gui()
{
  for(std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
    it != components.end(); it++)
  {
    (*it)->gui();
  }
}

std::shared_ptr<Transform> Entity::getTransform()
{
  return getComponent<Transform>();
}

void Entity::kill()
{
  alive = false;
}

bool Entity::isAlive()
{
  return alive;
}
