#include "Gui.h"
#include "Texture.h"
#include "Platform.h"
#include "Window.h"

std::sr1::shared_ptr<Gui> Gui::initialize(std::shared_ptr<Platform> platform)
{
  std::sr1::shared_ptr<Gui> rtn = std::sr1::make_shared<Gui>();
  rtn->platform = platform;

  return rtn;
}

void Gui::image(qsoft::Vector2 position, std::shared_ptr<Texture> texture)
{
  std::shared_ptr<qsoft::Texture> buffer = platform.lock()->getWindow()->getBuffer();

  for(size_t y = 0; y < texture->getHeight(); y++)
  {
    for(size_t x = 0; x < texture->getWidth(); x++)
    {
      qsoft::Color p = texture->getPixel(x, y);
      //qsoft::Color curr = buffer->getPixel(position.x + x, position.y + y);

      //p.r = (curr.r + (p.r * p.a / 255)) / 2;
      //p.g = (curr.g + (p.g * p.a / 255)) / 2;
      //p.b = (curr.b + (p.b * p.a / 255)) / 2;
      if(p.a != 255) continue;

      buffer->setPixel(position.x + x, position.y + y, p);
    }
  }
}

void Gui::image(qsoft::Vector2 position, std::shared_ptr<Texture> texture, qsoft::Vector4 clip)
{
  std::shared_ptr<qsoft::Texture> buffer = platform.lock()->getWindow()->getBuffer();

  for(size_t y = clip.y; y < clip.y + clip.w; y++)
  {
    for(size_t x = clip.x; x < clip.x + clip.z; x++)
    {
      qsoft::Color p = texture->getPixel(x, y);

      if(p.a != 255) continue;

      buffer->setPixel(position.x + (x - clip.x), position.y + (y - clip.y), p);
    }
  }
}
