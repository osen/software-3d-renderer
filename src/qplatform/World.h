#include "Entity.h"
#include "Exception.h"

#include <sr1/noncopyable>
#include <sr1/memory>

#include <vector>

class Platform;

class World : public std::sr1::noncopyable
{
  friend class Platform; // For initialize(), tick().

public:
  void reset();
  std::sr1::shared_ptr<Entity> addEntity();

  template <typename T>
  std::sr1::shared_ptr<Entity> addEntity()
  {
    std::sr1::shared_ptr<Entity> rtn = addEntity();
    rtn->addComponent<T>();

    return rtn;
  }

  template <typename T>
  std::sr1::shared_ptr<Entity> getEntity()
  {
    for(std::vector<std::sr1::shared_ptr<Entity> >::iterator eit = entities.begin();
      eit != entities.end(); eit++)
    {
      if(!(*eit)->alive) continue;

      if((*eit)->hasComponent<T>())
      {
        return *eit;
      }
    }

    throw Exception("Failed to obtain entity with specified type");
  }

  template <typename T>
  void getEntities(std::vector<std::sr1::shared_ptr<Entity> >& found)
  {
    for(std::vector<std::sr1::shared_ptr<Entity> >::iterator eit = entities.begin();
      eit != entities.end(); eit++)
    {
      if(!(*eit)->alive) continue;

      if((*eit)->hasComponent<T>())
      {
        found.push_back(*eit);
      }
    }
  }

private:
  static std::sr1::shared_ptr<World> initialize(std::sr1::shared_ptr<Platform>& platform);

  std::sr1::weak_ptr<Platform> platform;
  std::vector<std::sr1::shared_ptr<Entity> > entities;

  void tick();
  void display();
  void gui();

};
