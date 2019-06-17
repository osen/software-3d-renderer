#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class HitBox : public Component
{
  std::sr1::weak_ptr<Entity> owner;
  std::sr1::zero_initialized<float> timeout;

  void onTick();

public:
  void onInit(std::sr1::shared_ptr<Entity> owner);

  std::sr1::shared_ptr<Entity> getOwner();

};
