#include "Component.h"

#include <qsoft/qsoft.h>

class Transform : public Component
{
  qsoft::Vector3 position;
  qsoft::Vector3 rotation;
  qsoft::Vector3 scale;

public:
  void onInit();

  qsoft::Matrix getModelMatrix();
  qsoft::Vector3 getPosition();
  qsoft::Vector3 getRotation();
  void translate(qsoft::Vector3 translation);
  void setPosition(qsoft::Vector3 position);
  void setRotation(qsoft::Vector3 rotation);
  void setScale(qsoft::Vector3 scale);
  void lookAt(qsoft::Vector3 position);

};
