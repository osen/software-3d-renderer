#include <qsoft/qsoft.h>

#include <vector>
#include <sr1/memory>

class ModelRenderer;
class Texture;
class Model;
class StaticModelCollider;

class MaterialGroup
{
  friend class ModelRenderer;
  friend class StaticModelCollider;

  qsoft::Mesh mesh;
  std::sr1::shared_ptr<Texture> texture;

public:
  void addFace(qsoft::Face& f);
  void setTexture(std::sr1::shared_ptr<Texture> texture);

};
