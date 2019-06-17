#include "World.h"
#include "Entity.h"
#include "Transform.h"

std::sr1::shared_ptr<World> World::initialize(std::sr1::shared_ptr<Platform>& platform)
{
  std::sr1::shared_ptr<World> rtn = std::sr1::make_shared<World>();
  rtn->platform = platform;

  return rtn;
}

void World::reset()
{
  for(std::vector<std::sr1::shared_ptr<Entity> >::iterator it = entities.begin();
    it != entities.end(); it++)
  {
    (*it)->kill();
  }
}

std::sr1::shared_ptr<Entity> World::addEntity()
{
  std::sr1::shared_ptr<Entity> rtn = std::sr1::make_shared<Entity>();

  rtn->alive = true;
  rtn->self = rtn;
  rtn->platform = platform;
  entities.push_back(rtn);
  rtn->addComponent<Transform>();

  return rtn;
}

void World::tick()
{
/*
  for(std::vector<std::sr1::shared_ptr<Entity> >::iterator it = entities.begin();
    it != entities.end(); it++)
  {
    (*it)->tick();
  }
*/

  for(size_t i = 0; i < entities.size(); i++)
  {
    entities.at(i)->tick();
  }

  for(std::vector<std::sr1::shared_ptr<Entity> >::iterator it = entities.begin();
    it != entities.end();)
  {
    if((*it)->alive == false)
    {
      it = entities.erase(it);
    }
    else
    {
      it++;
    }
  }
}

void World::display()
{
  for(std::vector<std::sr1::shared_ptr<Entity> >::iterator it = entities.begin();
    it != entities.end(); it++)
  {
    (*it)->display();
  }
}

void World::gui()
{
  for(std::vector<std::sr1::shared_ptr<Entity> >::iterator it = entities.begin();
    it != entities.end(); it++)
  {
    (*it)->gui();
  }
}
