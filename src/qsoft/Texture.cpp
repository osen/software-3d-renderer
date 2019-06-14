#include "Texture.h"
#include "Color.h"

#include <sr1/zero_initialized>

#include <vector>

#include <cstring>

namespace qsoft
{

struct TextureImpl : public Texture
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

  void clear()
  {
    memset(&data.at(0), 0, data.size() * sizeof(data.at(0)));
    memset(&depthBuffer.at(0), 0, data.size() * sizeof(data.at(0)));
  }

  Color getPixel(int x, int y)
  {
    if(x > width || x < 0 || y > height || y < 0)
    {
      throw std::exception();
    }

    //return *(data.begin() + y * width + x);
    return data.at(y * width + x);
  }

  void setPixel(int x, int y, const Color& color)
  {
    if(x < 0 || y < 0)
    {
      return;
    }

    if(x >= width || y >= height)
    {
      return;
    }

    //*(data.begin() + y * width + x) = color;
    data.at(y * width + x) = color;

    if(!raw)
    {
      return;
    }

    double pw = 1;
    double ph = 1;

    if(rawStretch)
    {
      pw = (float)rawWidth / (float)width;
      ph = (float)rawHeight / (float)height;
      x = x * pw;
      y = y * ph;
      pw ++;
      ph ++;
    }

    int bpp = rawBpp;
    bool bgr = rawBgr;

    for(int yi = 0; yi < ph; yi++)
    {
      if(y + yi >= rawHeight) break;

      unsigned char *yp = raw + rawWidth * bpp * (y + yi);
      unsigned char *xp = yp + x * bpp;

      for(int xi = 0; xi < pw; xi++)
      {
        if(x + xi >= rawWidth) break;

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

  int getWidth() const
  {
    return width;
  }

  int getHeight() const
  {
    return height;
  }

  float getDepth(int x, int y)
  {
    return depthBuffer.at(y * width + x);
  }

  void setDepth(int x, int y, float depth)
  {
    depthBuffer.at(y * width + x) = depth;
  }

  void setRaw(unsigned char *raw, int width, int height, int format)
  {
    this->raw = raw;
    rawWidth = width;
    rawHeight = height;

    rawBpp = 3;
    rawStretch = false;
    rawBgr = false;

    if(format == 4)
    {
      rawBpp = 4;
    }
    else if(format == 5)
    {
      rawBpp = 4;
      rawBgr = true;
    }
    else if(format == 6)
    {
      rawBgr = true;
    }
    else if(format == 13)
    {
      rawStretch = true;
      rawWidth = width;
      rawHeight = height;
    }
    else if(format == 14)
    {
      rawBpp = 4;
      rawStretch = true;
      rawWidth = width;
      rawHeight = height;
    }
    else if(format == 15)
    {
      rawBpp = 4;
      rawBgr = true;
      rawStretch = true;
      rawWidth = width;
      rawHeight = height;
    }
    else if(format == 16)
    {
      rawBgr = true;
      rawStretch = true;
      rawWidth = width;
      rawHeight = height;
    }

    //printf("%i %i %i\n", (int)rawBpp, (int)rawStretch, (int)rawBgr);
  }
};

std::sr1::shared_ptr<Texture> Texture::create(int width, int height)
{
  std::sr1::shared_ptr<TextureImpl> impl = std::sr1::make_shared<TextureImpl>();

  impl->data.resize(width * height);
  impl->depthBuffer.resize(width * height);
  impl->width = width;
  impl->height = height;

  return impl;
}

}
