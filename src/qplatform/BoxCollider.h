#include "Component.h"

#include <qsoft/qsoft.h>

class BoxCollider : public Component
{
public:
  void onInit();

  void setOffset(const qsoft::Vector3& offset);
  void setSize(const qsoft::Vector3& size);

private:
  void onTick();

  qsoft::Vector3 size;
  qsoft::Vector3 offset;
  qsoft::Vector3 lastPosition;
};
