#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class Player : public Component
{
  std::sr1::shared_ptr<Model> model;
  std::sr1::shared_ptr<Texture> pitchfork;
  std::sr1::shared_ptr<Texture> heart;
  std::sr1::shared_ptr<ModelRenderer> modelRenderer;
  std::sr1::zero_initialized<float> speed;
  std::sr1::zero_initialized<float> health;
  std::sr1::zero_initialized<float> attack;
  std::sr1::shared_ptr<Font> font;
  std::sr1::shared_ptr<Texture> hudBar;
  std::sr1::shared_ptr<Texture> hudIndent;

  void onTick();
  void onGui();
  void doAttack();
  void checkHits();

public:
  void onInit();

};
