#include "Vector.h"

#include <cmath>

namespace qsoft
{

Vector2::Vector2() : x(0), y(0) { }

Vector2::Vector2(float x, float y)
{
  this->x = x;
  this->y = y;
}

Vector3::Vector3() : x(0), y(0), z(0) { }

Vector3::Vector3(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3::Vector3(const Vector4& value)
{
  x = value.x;
  y = value.y;
  z = value.z;
}

Vector3 Vector3::operator-(float value)
{
  return Vector3(x - value, y - value, z - value);
}

Vector3 Vector3::operator+(float value)
{
  return Vector3(x + value, y + value, z + value);
}

Vector3 Vector3::operator/(float value)
{
  return Vector3(x / value, y / value, z / value);
}

Vector3 Vector3::operator*(float value)
{
  return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator-(const Vector3& other)
{
  return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator+(const Vector3& other)
{
  return Vector3(x + other.x, y + other.y, z + other.z);
}

float Vector3::dot(const Vector3& a, const Vector3& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vector3::length() const
{
  return sqrt(dot(*this, *this));
}

Vector3 Vector3::normalize() const
{
  float l = length();
  Vector3 r;
  r.x = x / l;
  r.y = y / l;
  r.z = z / l;
  return r;
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
  Vector3 r;

  r.x = a.y * b.z - b.y * a.z;
  r.y = a.z * b.x - b.z * a.x;
  r.z = a.x * b.y - b.x * a.y;

  return r;
}

Vector4::Vector4() : x(0), y(0), z(0), w(0) { }

Vector4::Vector4(float x, float y, float z, float w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

Vector4::Vector4(Vector3& value, float w)
{
  x = value.x;
  y = value.y;
  z = value.z;
  this->w = w;
}

Vector4& Vector4::operator=(const Vector3& other)
{
  x = other.x;
  y = other.y;
  z = other.z;
  w = 1;
  return *this;
}

}

