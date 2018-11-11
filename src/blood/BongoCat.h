#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class BongoCat : public Component
{
  std::shared_ptr<Texture> texture;
  std::shared_ptr<SpriteRenderer> spriteRenderer;
  std::shared_ptr<Sound> music;
  std::sr1::zero_initialized<float> frame;

  void onTick();

public:
  void onInit();

};
