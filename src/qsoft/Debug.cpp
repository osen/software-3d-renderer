#include "Debug.h"
#include "Vector.h"
#include "Matrix.h"
#include "Color.h"

#include <iostream>

namespace qsoft
{

void Debug::log(Matrix& m)
{
  std::cout << "Matrix:" << std::endl;
  std::cout << "[" << m.value[0][0] << "][" << m.value[0][1] << "][" << m.value[0][2] << "][" << m.value[0][3] << "]" << std::endl;
  std::cout << "[" << m.value[1][0] << "][" << m.value[1][1] << "][" << m.value[1][2] << "][" << m.value[1][3] << "]" << std::endl;
  std::cout << "[" << m.value[2][0] << "][" << m.value[2][1] << "][" << m.value[2][2] << "][" << m.value[2][3] << "]" << std::endl;
  std::cout << "[" << m.value[3][0] << "][" << m.value[3][1] << "][" << m.value[3][2] << "][" << m.value[3][3] << "]" << std::endl;
}

void Debug::log(Vector3& v)
{
  std::cout << "Vector3: [" << v.x << "][" << v.y << "][" << v.z << "]" << std::endl;
}

void Debug::log(Vector2& v)
{
  std::cout << "Vector2: [" << v.x << "][" << v.y << "]" << std::endl;
}

void Debug::log(Vector4& v)
{
  std::cout << "Vector4: [" << v.x << "][" << v.y << "][" << v.z << "][" << v.w << "]" << std::endl;
}

void Debug::log(const Color& c)
{
  std::cout << "Color: [" << (int)c.r << "][" << (int)c.g << "][" << (int)c.b << "][" << (int)c.a << "]" << std::endl;
}

}
