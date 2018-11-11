#include "Resource.h"
#include "Exception.h"

#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Platform;
class Texture;

class Resources
{
  friend class Platform; // for initialize()

public:
  template <typename T>
  std::shared_ptr<T> load(std::string path)
  {
    for(size_t i = 0; i < resources.size(); i++)
    {
      if(resources.at(i)->getPath() == path)
      {
        std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(resources.at(i));

        if(!rtn)
        {
          //throw Exception("Loaded resource '" + path + "' is of the incorrect type");
          continue;
        }

        return rtn;
      }
    }

    std::shared_ptr<T> rtn = std::make_shared<T>();
    rtn->platform = platform;
    rtn->load(path);

    resources.push_back(rtn);

    return rtn;

    // TODO: Try load from other paths
    //return std::shared_ptr<T>();
  }

  template <typename T, typename A, typename B>
  std::shared_ptr<T> create(A a, B b)
  {
    std::shared_ptr<T> rtn = std::make_shared<T>();
    rtn->platform = platform;
    rtn->onCreate(a, b);
    return rtn;
  }

  std::shared_ptr<Texture> getDefaultTexture();

private:
  static std::shared_ptr<Resources> initialize(std::shared_ptr<Platform>& platform);

  std::vector<std::shared_ptr<Resource> > resources;
  std::weak_ptr<Platform> platform;
  std::shared_ptr<Texture> defaultTexture;

};
