#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class Player : public Component
{
  std::shared_ptr<Model> model;
  std::shared_ptr<Texture> pitchfork;
  std::shared_ptr<Texture> heart;
  std::shared_ptr<ModelRenderer> modelRenderer;
  std::sr1::zero_initialized<float> speed;
  std::sr1::zero_initialized<float> health;
  std::sr1::zero_initialized<float> attack;

  void onTick();
  void onGui();
  void doAttack();
  void checkHits();

public:
  void onInit();

};
