#include "BoxCollider.h"
#include "StaticModelCollider.h"
#include "World.h"
#include "Transform.h"

void BoxCollider::onInit()
{
  size = qsoft::Vector3(1, 1, 1);
  lastPosition = getTransform()->getPosition();
}

void BoxCollider::setOffset(const qsoft::Vector3& offset)
{
  this->offset = offset;
}

void BoxCollider::setSize(const qsoft::Vector3& size)
{
  this->size = size;
}

void BoxCollider::onTick()
{
  std::vector<std::shared_ptr<Entity> > smces;

  getWorld()->getEntities<StaticModelCollider>(smces);

  qsoft::Vector3 np = getTransform()->getPosition() + offset;

  for(std::vector<std::shared_ptr<Entity> >::iterator it = smces.begin();
    it != smces.end(); it++)
  {
    std::shared_ptr<StaticModelCollider> smc =
      (*it)->getComponent<StaticModelCollider>();

    bool solved = false;
    qsoft::Vector3 sp = smc->getCollisionResponse(np, size, solved);

    if(solved)
    {
      np = sp;
    }
    else
    {
      np = lastPosition + offset;
    }

    np = np - offset;
    getTransform()->setPosition(np);
    lastPosition = np;
  }
}

