#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class Zombie : public Component
{
  std::shared_ptr<Texture> texture;
  std::shared_ptr<SpriteRenderer> spriteRenderer;
  std::shared_ptr<Sound> groan;
  std::shared_ptr<Sound> activateGroan;
  std::sr1::zero_initialized<float> frame;
  std::sr1::zero_initialized<float> attack;
  std::sr1::zero_initialized<int> state;

  void onTick();
  void checkHits();
  void doAttack();

public:
  void onInit();
  void activate();

};
