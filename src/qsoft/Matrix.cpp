#include "Matrix.h"
#include "Vector.h"
#include "Util.h"

#include <cstring>
#include <cmath>

#define PI 3.14f

namespace qsoft
{

Matrix::Matrix()
{
  memset(value, 0, sizeof(value));
}

Matrix Matrix::identity()
{
  Matrix m;

  m.value[0][0] = 1.0f;
  m.value[1][1] = 1.0f;
  m.value[2][2] = 1.0f;
  m.value[3][3] = 1.0f;

  return m;
}

Matrix Matrix::viewport(int x, int y, int width, int height)
{
  float hw = width / 2.0f;
  float hh = height / 2.0f;

  Matrix m = identity();
  m.value[0][3] = x + hw;
  m.value[1][3] = y + hh;
  m.value[0][0] = hw;
  m.value[1][1] = -hh;

  return m;
}

Matrix Matrix::translation(const Vector3& value)
{
  Matrix m = identity();

  m.value[0][3] = value.x;
  m.value[1][3] = value.y;
  m.value[2][3] = value.z;

  return m;
}

Matrix Matrix::scale(const Vector3& value)
{
  Matrix m = identity();

  m.value[0][0] = value.x;
  m.value[1][1] = value.y;
  m.value[2][2] = value.z;

  return m;
}

Matrix Matrix::rotation(const Vector3& axis, float a)
{
  a = a * PI / 180.0f;
  Matrix m = identity();

  float c = cos(a);
  float s = sin(a);
  float t = 1.0f - c;

  Vector3 naxis = axis.normalize();
  float x = naxis.x;
  float y = naxis.y;
  float z = naxis.z;

  m.value[0][0] = 1 + t * (x * x - 1);
  m.value[0][1] = z * s + t * x * y;
  m.value[0][2] = -y * s + t * x * z;
  m.value[0][3] = 0.0f;

  m.value[1][0] = -z * s + t * x * y;
  m.value[1][1] = 1 + t * (y * y - 1);
  m.value[1][2] = x * s + t * y * z;
  m.value[1][3] = 0.0f;

  m.value[2][0] = y * s + t * x * z;
  m.value[2][1] = -x * s + t * y * z;
  m.value[2][2] = 1 + t * (z * z - 1);
  m.value[2][3] = 0.0f;

  m.value[3][0] = 0.0f;
  m.value[3][1] = 0.0f;
  m.value[3][2] = 0.0f;
  m.value[3][3] = 1.0f;

  return m;
}

Matrix Matrix::rotation(const Vector3& value)
{
  float mag = fabs(value.x) + fabs(value.y) + fabs(value.z);
  float xc = 0;
  float yc = 0;
  float zc = 0;

  if(mag <= 0)
  {
    return Matrix::identity();
  }

  if(value.x != 0) xc = mag / value.x;
  if(value.y != 0) yc = mag / value.y;
  if(value.z != 0) zc = mag / value.z;

  Vector3 v = Vector3(xc, yc, zc);

  return rotation(v, mag);

/*
  // TODO: Weak slow.
  return rotation(Vector3(1, 0, 0), value.x) *
    rotation(Vector3(0, 1, 0), value.y) *
    rotation(Vector3(0, 0, 1), value.z);
*/
}

Matrix Matrix::perspective(float fov, float aspect, float znear, float zfar)
{
  Matrix m;

  fov = Util::degToRad(fov);

  float tanHalfFOV = tan(fov / 2.0f);
  float zrange = znear - zfar;

  m.value[0][0] = 1.0f / (tanHalfFOV * aspect);
  m.value[0][1] = 0;
  m.value[0][2] = 0;
  m.value[0][3] = 0;
  m.value[1][0] = 0;
  m.value[1][1] = 1.0f / tanHalfFOV;
  m.value[1][2] = 0;
  m.value[1][3] = 0;
  m.value[2][0] = 0;
  m.value[2][1] = 0;
  m.value[2][2] = (-znear - zfar) / zrange;
  m.value[2][3] = 2 * zfar * znear / zrange;
  m.value[3][0] = 0;
  m.value[3][1] = 0;
  m.value[3][2] = 1;
  m.value[3][3] = 0;

  return m;
}

Matrix Matrix::operator*(const Matrix& other)
{
  Matrix r;

  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 4; i++)
    {
      r.value[j][i] =
        value[j][0] * other.value[0][i] +
        value[j][1] * other.value[1][i] +
        value[j][2] * other.value[2][i] +
        value[j][3] * other.value[3][i];
    }
  }

  return r;
}

Vector4 Matrix::operator*(const Vector4& b)
{
  Vector4 r;

  r.x = b.x * value[0][0] + b.y * value[0][1] + b.z * value[0][2] + b.w * value[0][3];
  r.y = b.x * value[1][0] + b.y * value[1][1] + b.z * value[1][2] + b.w * value[1][3];
  r.z = b.x * value[2][0] + b.y * value[2][1] + b.z * value[2][2] + b.w * value[2][3];
  r.w = b.x * value[3][0] + b.y * value[3][1] + b.z * value[3][2] + b.w * value[3][3];

  return r;
}

Matrix Matrix::inverse(const Matrix& value)
{
  float s[6];
  float c[6];
  s[0] = value.value[0][0]*value.value[1][1] - value.value[0][1]*value.value[1][0];
  s[1] = value.value[0][0]*value.value[2][1] - value.value[0][1]*value.value[2][0];
  s[2] = value.value[0][0]*value.value[3][1] - value.value[0][1]*value.value[3][0];
  s[3] = value.value[1][0]*value.value[2][1] - value.value[1][1]*value.value[2][0];
  s[4] = value.value[1][0]*value.value[3][1] - value.value[1][1]*value.value[3][0];
  s[5] = value.value[2][0]*value.value[3][1] - value.value[2][1]*value.value[3][0];

  c[0] = value.value[0][2]*value.value[1][3] - value.value[0][3]*value.value[1][2];
  c[1] = value.value[0][2]*value.value[2][3] - value.value[0][3]*value.value[2][2];
  c[2] = value.value[0][2]*value.value[3][3] - value.value[0][3]*value.value[3][2];
  c[3] = value.value[1][2]*value.value[2][3] - value.value[1][3]*value.value[2][2];
  c[4] = value.value[1][2]*value.value[3][3] - value.value[1][3]*value.value[3][2];
  c[5] = value.value[2][2]*value.value[3][3] - value.value[2][3]*value.value[3][2];

  /* Assumes it is invertible */
  float idet = 1.0f/( s[0]*c[5]-s[1]*c[4]+s[2]*c[3]+s[3]*c[2]-s[4]*c[1]+s[5]*c[0] );

  Matrix r;

  r.value[0][0] = ( value.value[1][1] * c[5] - value.value[2][1] * c[4] + value.value[3][1] * c[3]) * idet;
  r.value[1][0] = (-value.value[1][0] * c[5] + value.value[2][0] * c[4] - value.value[3][0] * c[3]) * idet;
  r.value[2][0] = ( value.value[1][3] * s[5] - value.value[2][3] * s[4] + value.value[3][3] * s[3]) * idet;
  r.value[3][0] = (-value.value[1][2] * s[5] + value.value[2][2] * s[4] - value.value[3][2] * s[3]) * idet;

  r.value[0][1] = (-value.value[0][1] * c[5] + value.value[2][1] * c[2] - value.value[3][1] * c[1]) * idet;
  r.value[1][1] = ( value.value[0][0] * c[5] - value.value[2][0] * c[2] + value.value[3][0] * c[1]) * idet;
  r.value[2][1] = (-value.value[0][3] * s[5] + value.value[2][3] * s[2] - value.value[3][3] * s[1]) * idet;
  r.value[3][1] = ( value.value[0][2] * s[5] - value.value[2][2] * s[2] + value.value[3][2] * s[1]) * idet;

  r.value[0][2] = ( value.value[0][1] * c[4] - value.value[1][1] * c[2] + value.value[3][1] * c[0]) * idet;
  r.value[1][2] = (-value.value[0][0] * c[4] + value.value[1][0] * c[2] - value.value[3][0] * c[0]) * idet;
  r.value[2][2] = ( value.value[0][3] * s[4] - value.value[1][3] * s[2] + value.value[3][3] * s[0]) * idet;
  r.value[3][2] = (-value.value[0][2] * s[4] + value.value[1][2] * s[2] - value.value[3][2] * s[0]) * idet;

  r.value[0][3] = (-value.value[0][1] * c[3] + value.value[1][1] * c[1] - value.value[2][1] * c[0]) * idet;
  r.value[1][3] = ( value.value[0][0] * c[3] - value.value[1][0] * c[1] + value.value[2][0] * c[0]) * idet;
  r.value[2][3] = (-value.value[0][3] * s[3] + value.value[1][3] * s[1] - value.value[2][3] * s[0]) * idet;
  r.value[3][3] = ( value.value[0][2] * s[3] - value.value[1][2] * s[1] + value.value[2][2] * s[0]) * idet;

  return r;
}

}
