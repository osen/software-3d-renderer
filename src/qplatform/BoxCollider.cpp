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
  collideStaticMesh();
  collideBox();
}

void BoxCollider::collideBox()
{
  std::vector<std::sr1::shared_ptr<Entity> > bces;

  getWorld()->getEntities<BoxCollider>(bces);
  qsoft::Vector3 np = getTransform()->getPosition() + offset;

  for(std::vector<std::sr1::shared_ptr<Entity> >::iterator it = bces.begin();
    it != bces.end(); it++)
  {
    if(*it == getEntity())
    {
      continue;
    }

    std::sr1::shared_ptr<BoxCollider> bc =
      (*it)->getComponent<BoxCollider>();

    qsoft::Vector3 sp = bc->getCollisionResponse(np, size);
    np = sp;
    np = np - offset;
    getTransform()->setPosition(np);
    lastPosition = np;
  }
}

void BoxCollider::collideStaticMesh()
{
  std::vector<std::sr1::shared_ptr<Entity> > smces;

  getWorld()->getEntities<StaticModelCollider>(smces);

  qsoft::Vector3 np = getTransform()->getPosition() + offset;

  for(std::vector<std::sr1::shared_ptr<Entity> >::iterator it = smces.begin();
    it != smces.end(); it++)
  {
    std::sr1::shared_ptr<StaticModelCollider> smc =
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

bool BoxCollider::isColliding(qsoft::Vector3 position, qsoft::Vector3 size)
{
  qsoft::Vector3 a = getTransform()->getPosition() + offset;
  qsoft::Vector3& as = this->size;
  qsoft::Vector3& b = position;
  qsoft::Vector3& bs = size;

  if(a.x > b.x) // a right of b
  {
    if(a.x - as.x > b.x + bs.x) // left edge of a greater than right edge of b (not colliding)
    {
      return false;
    }
  }
  else
  {
    if(b.x - bs.x > a.x + as.x)
    {
      return false;
    }
  }

  if(a.z > b.z) // a front of b
  {
    if(a.z - as.z > b.z + bs.z) // back edge of a greater than front edge of b (not colliding)
    {
      return false;
    }
  }
  else
  {
    if(b.z - bs.z > a.z + as.z)
    {
      return false;
    }
  }

  if(a.y > b.y) // a above b
  {
    if(a.y - as.y > b.y + bs.y) // bottom edge of a greater than top edge of b (not colliding)
    {
      return false;
    }
  }
  else
  {
    if(b.y - bs.y > a.y + as.y)
    {
      return false;
    }
  }

  return true;
}

qsoft::Vector3 BoxCollider::getCollisionResponse(qsoft::Vector3 position,
    qsoft::Vector3 size)
{
  float amount = 0.1f;
  float step = 0.1f;

  while(true)
  {
    if(!isColliding(position, size)) break;
    position.x += amount;
    if(!isColliding(position, size)) break;
    position.x -= amount;
    position.x -= amount;
    if(!isColliding(position, size)) break;
    position.x += amount;
    position.z += amount;
    if(!isColliding(position, size)) break;
    position.z -= amount;
    position.z -= amount;
    if(!isColliding(position, size)) break;
    position.z += amount;
    position.y += amount;
    if(!isColliding(position, size)) break;
    position.y -= amount;
    position.y -= amount;
    if(!isColliding(position, size)) break;
    position.y += amount;
    amount += step;
  }

  return position;
}

