#include "Resource.h"

void Resource::onLoad(std::string path) { }

void Resource::load(std::string path)
{
  this->path = path;
  onLoad(path);
}

std::shared_ptr<Platform> Resource::getPlatform()
{
  return platform.lock();
}

std::string Resource::getPath()
{
  return path;
}
