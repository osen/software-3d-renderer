#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class Fade : public Component
{
  std::shared_ptr<Texture> overlay;
  std::sr1::zero_initialized<float> amount;
  std::sr1::zero_initialized<bool> fadeIn;
  std::sr1::zero_initialized<bool> disable;

  void onTick();
  void onGui();

public:
  void onInit();

};
