#include "Resource.h"
#include "Exception.h"
#include "Environment.h"
#include "Platform.h"

#include <sr1/memory>

#include <vector>
#include <string>
#include <iostream>

class Texture;

class Resources
{
  friend class Platform; // for initialize()

public:
  template <typename T>
  std::sr1::shared_ptr<T> load(std::string path)
  {
    if(path.find(platform.lock()->getEnvironment()->getDataPath() + "/") != 0)
    {
      path = platform.lock()->getEnvironment()->getDataPath() + "/" + path;
    }

    for(size_t i = 0; i < resources.size(); i++)
    {
      if(resources.at(i)->getPath() == path)
      {
        std::sr1::shared_ptr<T> rtn = std::sr1::dynamic_pointer_cast<T>(resources.at(i));

        if(!rtn)
        {
          //throw Exception("Loaded resource '" + path + "' is of the incorrect type");
          continue;
        }

        return rtn;
      }
    }

    std::sr1::shared_ptr<T> rtn = std::sr1::make_shared<T>();
    rtn->platform = platform;
    rtn->load(path);

    resources.push_back(rtn);

    return rtn;

    // TODO: Try load from other paths
    //return std::sr1::shared_ptr<T>();
  }

  template <typename T, typename A, typename B>
  std::sr1::shared_ptr<T> create(A a, B b)
  {
    std::sr1::shared_ptr<T> rtn = std::sr1::make_shared<T>();
    rtn->platform = platform;
    rtn->onCreate(a, b);
    return rtn;
  }

  std::sr1::shared_ptr<Texture> getDefaultTexture();

private:
  static std::sr1::shared_ptr<Resources> initialize(std::sr1::shared_ptr<Platform>& platform);

  std::vector<std::sr1::shared_ptr<Resource> > resources;
  std::sr1::weak_ptr<Platform> platform;
  std::sr1::shared_ptr<Texture> defaultTexture;

};
