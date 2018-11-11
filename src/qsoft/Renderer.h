#include <memory>

namespace qsoft
{

struct RendererImpl;
class Mesh;
class Texture;
struct Matrix;

class Renderer
{
  std::shared_ptr<RendererImpl> impl;

public:
  Renderer();

  void setMesh(const Mesh& mesh);
  void setTexture(const Texture& texture);
  void setView(const Matrix& view);
  void setModel(const Matrix& model);
  void setTarget(const Texture& target);
  void setProjection(const Matrix& projection);
  void render();

};

}
