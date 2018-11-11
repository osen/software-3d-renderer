#ifndef QSOFT_VECTOR_H
#define QSOFT_VECTOR_H

namespace qsoft
{

struct Vector4;

struct Vector2
{
  float x;
  float y;

  Vector2();
  Vector2(float x, float y);
};

struct Vector3
{
  float x;
  float y;
  float z;

  Vector3();
  Vector3(float x, float y, float z);
  Vector3(Vector4& value);
  Vector3 normalize() const;
  float length() const;

  Vector3 operator+(float value);
  Vector3 operator-(float value);
  Vector3 operator-(const Vector3& other);
  Vector3 operator+(const Vector3& other);
  Vector3 operator/(float value);
  Vector3 operator*(float value);

  static float dot(const Vector3& a, const Vector3& b);
  static Vector3 cross(Vector3& a, Vector3& b);
};

struct Vector4
{
  float x;
  float y;
  float z;
  float w;

  Vector4();
  Vector4(float x, float y, float z, float w);
  Vector4(Vector3& value, float w);

  // TODO: Remove this hack (to hard code 1 in w).
  Vector4& operator=(const Vector3& other);
};

}

#endif
