#include "Resources.h"
#include "Texture.h"

#include <qsoft/qsoft.h>

std::sr1::shared_ptr<Resources> Resources::initialize(std::sr1::shared_ptr<Platform>& platform)
{
  std::sr1::shared_ptr<Resources> rtn = std::sr1::make_shared<Resources>();

  rtn->platform = platform;

  rtn->defaultTexture = rtn->create<Texture>(2, 2);
  rtn->defaultTexture->setPixel(0, 0, qsoft::Color(255, 0, 255));
  rtn->defaultTexture->setPixel(1, 0, qsoft::Color(0, 255, 0));
  rtn->defaultTexture->setPixel(0, 1, qsoft::Color(0, 0, 255));
  rtn->defaultTexture->setPixel(1, 1, qsoft::Color(255, 0, 0));

  return rtn;
}

std::sr1::shared_ptr<Texture> Resources::getDefaultTexture()
{
  return defaultTexture;
}
