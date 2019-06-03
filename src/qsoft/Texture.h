#include <sr1/memory>

namespace qsoft
{

struct TextureImpl;
struct Color;

class Texture
{
  std::sr1::shared_ptr<TextureImpl> impl;

public:
  Texture();
  Texture(int width, int height);

  void clear();
  void setPixel(int x, int y, const Color& color);
  Color getPixel(int x, int y);
  int getWidth() const;
  int getHeight() const;
  float getDepth(int x, int y);
  void setDepth(int x, int y, float depth);

};

}
