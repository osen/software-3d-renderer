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
  void setTexture(const std::sr1::shared_ptr<Texture>& texture);
  void setView(const Matrix& view);
  void setModel(const Matrix& model);
  void setViewport(int x, int y, int width, int height);
  void setTarget(const std::sr1::shared_ptr<Texture>& target);
  void setProjection(const Matrix& projection);
  void render();

};

}
