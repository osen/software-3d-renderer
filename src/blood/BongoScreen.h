#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class BongoScreen : public Component
{
  std::sr1::zero_initialized<float> timeout;

  void onTick();
  void addZombie();
  float generateRandom();

public:
  void onInit();

};
