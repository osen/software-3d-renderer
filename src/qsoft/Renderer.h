#include <sr1/memory>

namespace qsoft
{

struct RendererImpl;
class Mesh;
class Texture;
struct Matrix;
struct Shadow;

class Renderer
{
  std::sr1::shared_ptr<RendererImpl> impl;

public:
  Renderer();

  void setMesh(const Mesh& mesh);
  void setTexture(const Texture& texture);
  void setView(const Matrix& view);
  void setModel(const Matrix& model);
  void setViewport(int x, int y, int width, int height);
  void setTarget(const Texture& target);
  void setShadow(std::sr1::shared_ptr<Shadow> shadow);
  void setProjection(const Matrix& projection);
  void render();

};

}
