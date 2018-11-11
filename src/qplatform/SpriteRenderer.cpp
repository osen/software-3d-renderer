#include "SpriteRenderer.h"
#include "Texture.h"
#include "Platform.h"
#include "Transform.h"
#include "Window.h"
#include "Camera.h"

void SpriteRenderer::onInit()
{
  rows = 1;
  columns = 1;
  row = 0;
  column = 0;
  setLayout(rows, columns);
  setFrame(row, column);
}

void SpriteRenderer::updateMesh()
{
  mesh = qsoft::Mesh();

  float left = (1.0f / (float)columns) * (float)column;
  float right = left + (1.0f / (float)columns);

  float bottom = (1.0f / (float)rows) * (float)row;
  float top = bottom + (1.0f / (float)rows);
  top = 1.0f - top;
  bottom = 1.0f - bottom;

  //left = 0.0f;
  //right = 0.1f;
  //top = 0.0f;
  //bottom = 0.1f;

  qsoft::Face f;
  f.a.position = qsoft::Vector3(-0.5f, -0.5f, 0);
  f.a.texCoord = qsoft::Vector2(left, top);
  f.b.position = qsoft::Vector3(-0.5f, 0.5f, 0);
  f.b.texCoord = qsoft::Vector2(left, bottom);
  f.c.position = qsoft::Vector3(0.5f, 0.5f, 0);
  f.c.texCoord = qsoft::Vector2(right, bottom);
  mesh.addFace(f);
  f.a.position = qsoft::Vector3(-0.5f, -0.5f, 0);
  f.a.texCoord = qsoft::Vector2(left, top);
  f.b.position = qsoft::Vector3(0.5f, -0.5f, 0);
  f.b.texCoord = qsoft::Vector2(right, top);
  f.c.position = qsoft::Vector3(0.5f, 0.5f, 0);
  f.c.texCoord = qsoft::Vector2(right, bottom);
  mesh.addFace(f);
}

void SpriteRenderer::setLayout(int columns, int rows)
{
  this->rows = rows;
  this->columns = columns;
  updateMesh();
}

void SpriteRenderer::setFrame(int column, int row)
{
  this->row = row;
  this->column = column;
  updateMesh();
}

void SpriteRenderer::onInit(std::shared_ptr<Texture> texture)
{
  onInit();
  setTexture(texture);
}

void SpriteRenderer::setTexture(std::shared_ptr<Texture> texture)
{
  this->texture = texture;
}

std::shared_ptr<Texture> SpriteRenderer::getTexture()
{
  return texture;
}

void SpriteRenderer::onDisplay()
{
  std::shared_ptr<qsoft::Renderer> r = getPlatform()->getWindow()->getRenderer();
  std::shared_ptr<Window> w = getWindow();
  r->setProjection(qsoft::Matrix::perspective(65.0f, (float)w->getWidth() / (float)w->getHeight(), 0.01f, 100.0f));

  std::shared_ptr<Camera> camera = getWindow()->getCurrentCamera();
  std::shared_ptr<Transform> t = camera->getTransform();
  r->setView(qsoft::Matrix::inverse(t->getModelMatrix()));

  r->setModel(getTransform()->getModelMatrix());

  r->setTexture(*texture->data);
  r->setMesh(mesh);
  r->render();
}
