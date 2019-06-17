#include <qsoft/qsoft.h>

#include <sr1/zero_initialized>
#include <sr1/memory>

class Platform;
class Camera;

class Window
{
  friend class Platform;
  friend class Camera;

public:
  int getWidth();
  int getHeight();
  std::sr1::shared_ptr<qsoft::Renderer> getRenderer();
  std::sr1::shared_ptr<Camera> getCurrentCamera();
  std::sr1::shared_ptr<qsoft::Texture> getBuffer();
  std::sr1::shared_ptr<qsoft::Shadow> getShadow();

private:
  static std::sr1::shared_ptr<Window> initialize();

  std::sr1::zero_initialized<int> width;
  std::sr1::zero_initialized<int> height;

  std::sr1::weak_ptr<Camera> currentCamera;

  std::sr1::shared_ptr<qsoft::Texture> buffer;
  std::sr1::shared_ptr<qsoft::Renderer> renderer;
  std::sr1::shared_ptr<qsoft::Shadow> shadow;

};
