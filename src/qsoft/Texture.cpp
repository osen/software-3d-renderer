#include "Texture.h"
#include "Color.h"

#include <vector>

#include <cstring>

namespace qsoft
{

struct TextureImpl
{
  std::vector<Color> data;
  int width;
  int height;
  std::vector<float> depthBuffer;
};

Texture::Texture() { }

Texture::Texture(int width, int height) : impl(std::sr1::make_shared<TextureImpl>())
{
  impl->data.resize(width * height);
  impl->depthBuffer.resize(width * height);
  impl->width = width;
  impl->height = height;
}

void Texture::clear()
{
  memset(&impl->data.at(0), 0, impl->data.size() * sizeof(impl->data.at(0)));
  memset(&impl->depthBuffer.at(0), 0, impl->data.size() * sizeof(impl->data.at(0)));
}

Color Texture::getPixel(int x, int y)
{
  if(x > impl->width || x < 0 || y > impl->height || y < 0)
  {
    throw std::exception();
  }

  return *(impl->data.begin() + y * impl->width + x);
  //return impl->data.at(y * impl->width + x);
}

void Texture::setPixel(int x, int y, const Color& color)
{
  if(x < 0 || y < 0)
  {
    return;
  }

  if(x >= impl->width || y >= impl->height)
  {
    return;
  }

  *(impl->data.begin() + y * impl->width + x) = color;
  //impl->data.at(y * impl->width + x) = color;
}

int Texture::getWidth() const
{
  return impl->width;
}

int Texture::getHeight() const
{
  return impl->height;
}

float Texture::getDepth(int x, int y)
{
  return impl->depthBuffer.at(y * impl->width + x);
}

void Texture::setDepth(int x, int y, float depth)
{
  impl->depthBuffer.at(y * impl->width + x) = depth;
}

}
