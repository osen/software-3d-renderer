#include "Component.h"
#include <qsoft/qsoft.h>

#include <sr1/zero_initialized>

#include <vector>
#include <memory>

struct Extent
{
  qsoft::Vector3 max;
  qsoft::Vector3 min;
};

struct ColliderColumn
{
  qsoft::Vector3 position;
  qsoft::Vector3 size;
  std::vector<qsoft::Face> faces;

  bool isColliding(qsoft::Vector3 position, qsoft::Vector3 size);
};

class StaticModelCollider : public Component
{
  std::vector<std::shared_ptr<ColliderColumn> > cols;
  Extent extent;
  std::sr1::zero_initialized<float> resolution;
  std::sr1::zero_initialized<float> tryStep;
  std::sr1::zero_initialized<float> maxStep;
  std::sr1::zero_initialized<float> tryInc;
  std::sr1::zero_initialized<float> maxInc;

  void generateExtent();
  void addFace(qsoft::Face face);

public:
  void onInit();
  Extent getExtent();
  bool isColliding(qsoft::Vector3 position, qsoft::Vector3 size);

  qsoft::Vector3 getCollisionResponse(qsoft::Vector3 position, qsoft::Vector3 size,
    bool& solved, qsoft::Vector3 lastPosition);

};
