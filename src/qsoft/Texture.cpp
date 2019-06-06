#include "Texture.h"
#include "Color.h"

#include <sr1/zero_initialized>

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

  std::sr1::zero_initialized<unsigned char *> raw;
  std::sr1::zero_initialized<int> rawWidth;
  std::sr1::zero_initialized<int> rawHeight;
  std::sr1::zero_initialized<int> rawBpp;
  std::sr1::zero_initialized<bool> rawStretch;
  std::sr1::zero_initialized<bool> rawBgr;
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

  //return *(impl->data.begin() + y * impl->width + x);
  return impl->data.at(y * impl->width + x);
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

  //*(impl->data.begin() + y * impl->width + x) = color;
  impl->data.at(y * impl->width + x) = color;

  if(!impl->raw)
  {
    return;
  }

  unsigned char *raw = impl->raw;

  double rw = 1;
  double rh = 1;

  if(impl->rawStretch)
  {
    rw = (float)impl->rawWidth / (float)impl->width;
    rh = (float)impl->rawHeight / (float)impl->height;
  }

  int bpp = impl->rawBpp;
  bool bgr = impl->rawBgr;

  x = x * rw;
  y = y * rh;
  rw ++;
  rh ++;

  for(int yi = 0; yi < rh; yi++)
  {
    if(y + yi >= impl->rawHeight) break;

    unsigned char *yp = raw + impl->rawWidth * bpp * (y + yi);
    unsigned char *xp = yp + x * bpp;

    for(int xi = 0; xi < rw; xi++)
    {
      if(x + xi >= impl->rawWidth) break;

      if(bgr)
      {
        *(xp) = color.b;
        *(xp + 1) = color.g;
        *(xp + 2) = color.r;
      }
      else
      {
        *(xp) = color.r;
        *(xp + 1) = color.g;
        *(xp + 2) = color.b;
      }

      if(bpp == 4)
      {
        *(xp + 3) = 255;
        xp += 4;
      }
      else
      {
        xp += 3;
      }
    }
  }
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

void Texture::setRaw(unsigned char *raw, int width, int height, int format)
{
  impl->raw = raw;
  impl->rawWidth = width;
  impl->rawHeight = height;

  impl->rawBpp = 3;
  impl->rawStretch = true;
  impl->rawBgr = false;

  if(format == 4)
  {
    impl->rawBpp = 4;
  }
  else if(format == 5)
  {
    impl->rawBpp = 4;
    impl->rawBgr = true;
  }
  else if(format == 13)
  {
    impl->rawStretch = true;
  }
  else if(format == 14)
  {
    impl->rawBpp = 4;
    impl->rawStretch = true;
  }
  else if(format == 15)
  {
    impl->rawBpp = 4;
    impl->rawBgr = true;
    impl->rawStretch = true;
  }
}

}
