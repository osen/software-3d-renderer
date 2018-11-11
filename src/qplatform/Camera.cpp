#include "Camera.h"
#include "Window.h"
#include "Entity.h"

void Camera::onInit()
{
  getWindow()->currentCamera = getEntity()->getComponent<Camera>();
}
