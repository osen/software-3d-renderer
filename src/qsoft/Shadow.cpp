#include "Shadow.h"
#include "Color.h"

#include <sr1/zero_initialized>

namespace qsoft
{

struct ShadowImpl : public Shadow
{
  std::sr1::zero_initialized<unsigned char *> raw;
  std::sr1::zero_initialized<int> width;
  std::sr1::zero_initialized<int> height;
  std::sr1::zero_initialized<int> bpp;
  std::sr1::zero_initialized<bool> stretch;
  std::sr1::zero_initialized<bool> bgr;

  /*
   * format 3 is rgb, 4 is rgba, 5 is bgra
   * format 13 is rgb, 14 is rgba, 15 is bgra (stretched)
   */
  void setRaw(unsigned char *raw, int width, int height, int format)
  {
    this->raw = raw;
    this->width = width;
    this->height = height;

    if(format == 3)
    {
      bpp = 3;
    }
    else if(format == 4)
    {
      bpp = 4;
    }
    else if(format == 5)
    {
      bpp = 4;
      bgr = true;
    }
    else if(format == 13)
    {
      bpp = 3;
      stretch = true;
    }
    else if(format == 14)
    {
      bpp = 4;
      stretch = true;
    }
    else if(format == 15)
    {
      bgr = true;
      bpp = 4;
      stretch = true;
    }
  }

  void setPixel(int x, int y, const Color& color)
  {
    raw[0] = 0;
    raw[1] = 255;
    raw[2] = 255;
  }
};

std::sr1::shared_ptr<Shadow> Shadow::create()
{
  std::sr1::shared_ptr<ShadowImpl> rtn =
    std::sr1::make_shared<ShadowImpl>();

  return rtn;
}

}
