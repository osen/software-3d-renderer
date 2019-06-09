#ifndef QPLATFORM_RESOURCE_H
#define QPLATFORM_RESOURCE_H

#include <string>
#include <memory>

class Resources;
class Platform;

class Resource
{
  friend class Resources;

  virtual void onLoad(std::string path);
  void load(std::string path);

  std::weak_ptr<Platform> platform;
  std::string path;

public:
  std::shared_ptr<Platform> getPlatform();
  std::string getPath();
  std::shared_ptr<Resources> getResources();

};

#endif
