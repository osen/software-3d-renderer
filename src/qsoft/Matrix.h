#ifndef QSOFT_MATRIX_H
#define QSOFT_MATRIX_H

namespace qsoft
{

struct Vector3;
struct Vector4;

struct Matrix
{
  float value[4][4];

public:
  Matrix();

  Matrix operator*(const Matrix& other);
  Vector4 operator*(const Vector4& other);

  static Matrix identity();
  static Matrix translation(const Vector3& value);
  static Matrix rotation(const Vector3& value);
  static Matrix rotation(const Vector3& axis, float a);
  static Matrix scale(const Vector3& value);
  static Matrix perspective(float fov, float aspect, float znear, float zfar);
  static Matrix viewport(int x, int y, int width, int height);
  static Matrix inverse(const Matrix& value);

};

}

#endif
