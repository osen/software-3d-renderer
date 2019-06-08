#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class Pickup : public Component
{
  std::shared_ptr<SpriteRenderer> spriteRenderer;
  std::shared_ptr<Sound> collected;

public:
  void onInit();

};
