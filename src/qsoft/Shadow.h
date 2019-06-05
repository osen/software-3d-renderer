#include <sr1/memory>

namespace qsoft
{

struct Color;

struct Shadow
{
  static std::sr1::shared_ptr<Shadow> create();

  virtual void setRaw(unsigned char *raw,
    int width, int height, int format) = 0;

  virtual void setPixel(int x, int y, const Color& color) = 0;
};

}
