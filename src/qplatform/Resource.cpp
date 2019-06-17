#include "Resource.h"
#include "Platform.h"

void Resource::onLoad(std::string path) { }

void Resource::load(std::string path)
{
  this->path = path;
  onLoad(path);
}

std::sr1::shared_ptr<Platform> Resource::getPlatform()
{
  return platform.lock();
}

std::sr1::shared_ptr<Resources> Resource::getResources()
{
  return getPlatform()->getResources();
}

std::string Resource::getPath()
{
  return path;
}
