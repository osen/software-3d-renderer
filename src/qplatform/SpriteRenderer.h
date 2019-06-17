#include "Component.h"

#include <qsoft/qsoft.h>

#include <sr1/zero_initialized>

class Texture;

class SpriteRenderer : public Component
{
  qsoft::Mesh mesh;
  std::sr1::shared_ptr<Texture> texture;
  std::sr1::zero_initialized<int> rows;
  std::sr1::zero_initialized<int> columns;
  std::sr1::zero_initialized<int> row;
  std::sr1::zero_initialized<int> column;

  void updateMesh();
  void onDisplay();

public:
  void onInit();
  void onInit(std::sr1::shared_ptr<Texture> texture);
  void setTexture(std::sr1::shared_ptr<Texture> texture);
  std::sr1::shared_ptr<Texture> getTexture();
  void setLayout(int columns, int rows);
  void setFrame(int column, int row);

};
