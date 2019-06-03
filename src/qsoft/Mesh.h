#include <sr1/memory>
#include <vector>

namespace qsoft
{

struct MeshImpl;
struct Face;

class Mesh
{
  std::sr1::shared_ptr<MeshImpl> impl;

public:
  Mesh();

  std::vector<Face>& getFaces();
  void addFace(Face& face);

};

}
