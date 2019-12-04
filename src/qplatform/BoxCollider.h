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

  void collideStaticMesh();
  void collideBox();

  qsoft::Vector3 size;
  qsoft::Vector3 offset;
  qsoft::Vector3 lastPosition;

  bool isColliding(qsoft::Vector3 position, qsoft::Vector3 size);

  qsoft::Vector3 getCollisionResponse(qsoft::Vector3 position,
    qsoft::Vector3 size);
};
