#include "Texture.h"
#include "Exception.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cstdlib>

void Texture::onLoad(std::string path)
{
  int w = 0;
  int h = 0;
  int channels = 0;

  unsigned char *raw = stbi_load(std::string(path + ".png").c_str(), &w, &h, &channels, 4);

  if(!raw)
  {
    raw = stbi_load(std::string(path + ".jpg").c_str(), &w, &h, &channels, 4);
  }

  if(!raw)
  {
    throw Exception("Failed to load '" + path + "'");
  }

  data = std::make_shared<qsoft::Texture>(w, h);
  unsigned char *p = raw;

  for(size_t y = 0; y < h; y++)
  {
    for(size_t x = 0; x < w; x++)
    {
      data->setPixel(x, y, qsoft::Color(*(p + 0), *(p + 1), *(p + 2), *(p + 3)));
      p += 4;
    }
  }

  free(raw);
}

void Texture::setPixel(int x, int y, const qsoft::Color& color)
{
  data->setPixel(x, y, color);
}

int Texture::getWidth()
{
  return data->getWidth();
}

int Texture::getHeight()
{
  return data->getHeight();
}

qsoft::Color Texture::getPixel(int x, int y)
{
  return data->getPixel(x, y);
}

void Texture::onCreate(int width, int height)
{
  data = std::make_shared<qsoft::Texture>(width, height);
}
