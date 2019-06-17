#ifndef QPLATFORM_RESOURCE_H
#define QPLATFORM_RESOURCE_H

#include <sr1/memory>

#include <string>

class Resources;
class Platform;

class Resource
{
  friend class Resources;

  virtual void onLoad(std::string path);
  void load(std::string path);

  std::sr1::weak_ptr<Platform> platform;
  std::string path;

public:
  std::sr1::shared_ptr<Platform> getPlatform();
  std::string getPath();
  std::sr1::shared_ptr<Resources> getResources();

};

#endif
