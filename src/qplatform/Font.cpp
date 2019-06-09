#include "Font.h"
#include "Exception.h"
#include "Resources.h"
#include "Texture.h"

#include <cstring>

static const char *characters = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

void Font::onLoad(std::string path)
{
  texture = getResources()->load<Texture>(path);
  generateGlyphs();
}

void Font::generateGlyphs()
{
  int x = 0;

  for(size_t i = 0; i < strlen(characters); i++)
  {
    Glyph g;
    g.c = characters[i];
    g.texture = texture;
    g.rect.y = 0;
    g.rect.w = texture->getHeight();

    while(1)
    {
      if(x >= texture->getWidth())
      {
        throw Exception("End of image before all glyphs assigned");
      }

      if(dirtyColumn(x) == true)
      {
        g.rect.x = x;
        break;
      }

      x++;
    }

    while(1)
    {
      if(x >= texture->getWidth())
      {
        throw Exception("Glyph bounds went past end of image");
      }

      if(dirtyColumn(x) == 0)
      {
        g.rect.z = x - g.rect.x;
        break;
      }

      x++;
    }

    glyphs.push_back(g);

    if(g.c == '-')
    {
      g.c = ' ';
      g.rect.w = 1;
      glyphs.push_back(g);
    }
  }
}

bool Font::dirtyColumn(int x)
{
  for(int y = 0; y < texture->getHeight(); y++)
  {
    qsoft::Color col = texture->getPixel(x, y);

    if(col.a != 0) return true;
  }

  return false;
}

int Font::getWidth(const std::string& dample)
{
  return 1;
}

int Font::getHeight()
{
  return 1;
}

Glyph Font::getGlyph(char c)
{
  for(std::vector<Glyph>::iterator it = glyphs.begin();
    it != glyphs.end(); it++)
  {
    if(it->c == c)
    {
      return *it;
    }
  }

  throw Exception("The specified glyph was not found");
}
