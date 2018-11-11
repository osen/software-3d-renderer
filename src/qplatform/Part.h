#include <vector>
#include <memory>
#include <string>

class Model;
class MaterialGroup;
class StaticModelCollider;

class Part
{
  friend class Model;
  friend class StaticModelCollider;

  std::vector<std::shared_ptr<MaterialGroup> > materialGroups;
  std::string name;

public:
  void addMaterialGroup(std::shared_ptr<MaterialGroup> mg);
  std::shared_ptr<MaterialGroup> getMaterialGroup(size_t idx);
  size_t getMaterialGroupCount();
  std::string getName();

};
