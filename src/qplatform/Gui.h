#include <qsoft/qsoft.h>

#include <sr1/memory>

#include <memory>

class Platform;
class Texture;

class Gui
{
  friend class Platform;

  static std::sr1::shared_ptr<Gui> initialize(
    std::shared_ptr<Platform> platform);

  std::weak_ptr<Platform> platform;

public:
  void image(qsoft::Vector2 position, std::shared_ptr<Texture> texture);

  void image(qsoft::Vector2 position, std::shared_ptr<Texture> texture,
    qsoft::Vector4 clip);

  void image(qsoft::Vector4 position, std::shared_ptr<Texture> texture,
    qsoft::Vector4 clip);

  void rectangle(qsoft::Vector4 rect, const qsoft::Color& color);

};
