#ifndef QSOFT_COLOR_H
#define QSOFT_COLOR_H

namespace qsoft
{

struct Color
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;

  Color() : r(0), g(0), b(0), a(0) { }

  Color(unsigned char r, unsigned char g, unsigned char b)
  {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 255;
  }

  Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
  {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
};

}

#endif
