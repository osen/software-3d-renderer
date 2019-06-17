#include "Component.h"
#include <qsoft/qsoft.h>

#include <sr1/zero_initialized>
#include <sr1/memory>

#include <vector>

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

  void getColliding(qsoft::Vector3 position, qsoft::Vector3 size,
    std::vector<qsoft::Face>& collisions);
};

class StaticModelCollider : public Component
{
  std::vector<std::sr1::shared_ptr<ColliderColumn> > cols;
  Extent extent;
  std::sr1::zero_initialized<float> resolution;
  std::sr1::zero_initialized<float> tryStep;
  std::sr1::zero_initialized<float> maxStep;
  std::sr1::zero_initialized<float> tryInc;
  std::sr1::zero_initialized<float> maxInc;
  std::vector<qsoft::Face> collisions;

  void generateExtent();
  void addFace(qsoft::Face face);
  qsoft::Vector3 faceNormal(qsoft::Face& face);

public:
  void onInit();
  Extent getExtent();


  bool isColliding(qsoft::Face& face, qsoft::Vector3 position,
    qsoft::Vector3 size);

  bool isColliding(qsoft::Vector3 position, qsoft::Vector3 size);
  void getColliding(qsoft::Vector3 position, qsoft::Vector3 size);

  qsoft::Vector3 getCollisionResponse(qsoft::Vector3 position,
    qsoft::Vector3 size, bool& solved);

};
