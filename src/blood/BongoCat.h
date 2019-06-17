#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class BongoCat : public Component
{
  std::sr1::shared_ptr<Texture> texture;
  std::sr1::shared_ptr<SpriteRenderer> spriteRenderer;
  std::sr1::shared_ptr<Sound> music;
  std::sr1::zero_initialized<float> frame;

  void onTick();

public:
  void onInit();

};
