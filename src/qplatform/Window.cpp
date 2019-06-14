#include "Window.h"
#include "config.h"

std::shared_ptr<Window> Window::initialize()
{
  std::shared_ptr<Window> rtn = std::make_shared<Window>();

  rtn->width = DEFAULT_WINDOW_WIDTH;
  rtn->height = DEFAULT_WINDOW_HEIGHT;

  rtn->renderer = std::make_shared<qsoft::Renderer>();

  rtn->buffer = qsoft::Texture::create(320, 240);
  rtn->renderer->setTarget(rtn->buffer);

  return rtn;
}

std::sr1::shared_ptr<qsoft::Shadow> Window::getShadow()
{
  return shadow;
}

std::shared_ptr<qsoft::Renderer> Window::getRenderer()
{
  return renderer;
}

int Window::getWidth()
{
  return width;
}

int Window::getHeight()
{
  return height;
}

std::shared_ptr<Camera> Window::getCurrentCamera()
{
  return currentCamera.lock();
}

std::sr1::shared_ptr<qsoft::Texture> Window::getBuffer()
{
  return buffer;
}
