#include "Part.h"

void Part::addMaterialGroup(std::sr1::shared_ptr<MaterialGroup> mg)
{
  materialGroups.push_back(mg);
}

std::sr1::shared_ptr<MaterialGroup> Part::getMaterialGroup(size_t idx)
{
  return materialGroups.at(idx);
}

size_t Part::getMaterialGroupCount()
{
  return materialGroups.size();
}

std::string Part::getName()
{
  return name;
}
