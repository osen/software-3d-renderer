#include "Transform.h"

#include <cmath>

#define PI 3.14f

void Transform::onInit()
{
  scale = qsoft::Vector3(1, 1, 1);
}

void Transform::setPosition(qsoft::Vector3 position)
{
  this->position = position;
}

void Transform::setRotation(qsoft::Vector3 rotation)
{
  this->rotation = rotation;
}

void Transform::setScale(qsoft::Vector3 scale)
{
  this->scale = scale;
}

void Transform::translate(qsoft::Vector3 translation)
{
  qsoft::Vector4 fwd = qsoft::Matrix::rotation(rotation) *
    qsoft::Vector4(translation, 1);

  position = position + qsoft::Vector3(fwd);
}

qsoft::Matrix Transform::getModelMatrix()
{
  qsoft::Matrix rtn = qsoft::Matrix::identity();
  rtn = rtn * qsoft::Matrix::translation(position);
  rtn = rtn * qsoft::Matrix::rotation(rotation);
  rtn = rtn * qsoft::Matrix::scale(scale);

  return rtn;
}

qsoft::Vector3 Transform::getPosition()
{
  return position;
}

qsoft::Vector3 Transform::getRotation()
{
  return rotation;
}

void Transform::lookAt(qsoft::Vector3 position)
{
  float a = atan2(this->position.z - position.z,
    this->position.x - position.x);

  rotation.y = 90 + a * 180.0f / PI;
}

