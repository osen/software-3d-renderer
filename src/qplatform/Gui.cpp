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

void Gui::image(qsoft::Vector2 position, std::shared_ptr<Texture> texture,
  qsoft::Vector4 clip)
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

void Gui::rectangle(qsoft::Vector4 rect, const qsoft::Color& color)
{
  std::shared_ptr<qsoft::Texture> buffer =
    platform.lock()->getWindow()->getBuffer();

  for(size_t y = 0; y < rect.w; y++)
  {
    for(size_t x = 0; x < rect.z; x++)
    {
      buffer->setPixel(rect.x + x, rect.y + y, color);
    }
  }
}

void Gui::image(qsoft::Vector4 position, std::shared_ptr<Texture> texture,
  qsoft::Vector4 clip)
{
  std::shared_ptr<qsoft::Texture> buffer =
    platform.lock()->getWindow()->getBuffer();

  float scaleX = position.z / clip.z;
  float scaleY = position.w / clip.w;

  for(size_t y = clip.y; y < clip.y + clip.w; y++)
  {
    for(size_t x = clip.x; x < clip.x + clip.z; x++)
    {
      qsoft::Color p = texture->getPixel(x, y);

      if(p.a != 255) continue;

      qsoft::Vector4 v(position.x + (x - clip.x) * scaleX,
        position.y + (y - clip.y) * scaleY, scaleX, scaleY);

      for(size_t yp = 0; yp < v.w; yp++)
      {
        for(size_t xp = 0; xp < v.z; xp++)
        {
          buffer->setPixel(v.x + xp, v.y + yp, p);
        }
      }
    }
  }
}
