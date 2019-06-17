#include "Resource.h"

#include <qsoft/qsoft.h>

#include <sr1/zero_initialized>

#include <memory>
#include <vector>

class Texture;

struct Glyph
{
  std::sr1::zero_initialized<char> c;
  qsoft::Vector4 rect;
  std::sr1::shared_ptr<Texture> texture;
};

class Font : public Resource
{
  std::sr1::shared_ptr<Texture> texture;
  std::vector<Glyph> glyphs;

  void onLoad(std::string path);
  void generateGlyphs();
  bool dirtyColumn(int x);

public:
  int getWidth(const std::string& sample);
  int getHeight();
  Glyph getGlyph(char c);

};
