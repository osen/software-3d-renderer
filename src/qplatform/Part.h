#include <sr1/memory>

#include <vector>
#include <string>

class Model;
class MaterialGroup;
class StaticModelCollider;

class Part
{
  friend class Model;
  friend class StaticModelCollider;

  std::vector<std::sr1::shared_ptr<MaterialGroup> > materialGroups;
  std::string name;

public:
  void addMaterialGroup(std::sr1::shared_ptr<MaterialGroup> mg);
  std::sr1::shared_ptr<MaterialGroup> getMaterialGroup(size_t idx);
  size_t getMaterialGroupCount();
  std::string getName();

};
