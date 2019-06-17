#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class Zombie : public Component
{
  std::sr1::shared_ptr<Texture> texture;
  std::sr1::shared_ptr<SpriteRenderer> spriteRenderer;
  std::sr1::shared_ptr<Sound> groan;
  std::sr1::shared_ptr<Sound> activateGroan;
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
