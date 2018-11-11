namespace qsoft
{

struct Matrix;
struct Vector2;
struct Vector3;
struct Vector4;
struct Color;

struct Debug
{
  static void log(Matrix& m);
  static void log(Vector3& v);
  static void log(Vector2& v);
  static void log(Vector4& v);
  static void log(const Color& c);
};

}
