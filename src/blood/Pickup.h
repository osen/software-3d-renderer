#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class Pickup : public Component
{
  std::sr1::shared_ptr<SpriteRenderer> spriteRenderer;
  std::sr1::shared_ptr<Sound> collected;

public:
  void onInit();

};
