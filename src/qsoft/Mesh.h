#include <memory>
#include <vector>

namespace qsoft
{

struct MeshImpl;
struct Face;

class Mesh
{
  std::shared_ptr<MeshImpl> impl;

public:
  Mesh();

  std::vector<Face>& getFaces();
  void addFace(Face& face);

};

}
