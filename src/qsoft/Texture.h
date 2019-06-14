#include <sr1/memory>

namespace qsoft
{

struct Color;

struct Texture
{
  static std::sr1::shared_ptr<Texture> create(int width, int height);

  virtual void clear() = 0;
  virtual void setPixel(int x, int y, const Color& color) = 0;
  virtual Color getPixel(int x, int y) = 0;
  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;
  virtual float getDepth(int x, int y) = 0;
  virtual void setDepth(int x, int y, float depth) = 0;

  virtual void setRaw(unsigned char *raw, int width, int height, int format) = 0;

};

}
