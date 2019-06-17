#include "Resource.h"

#include <qsoft/qsoft.h>

#include <sr1/memory>

#include <vector>
#include <string>

class Part;
class ModelRenderer;
class Texture;
class Material;
class StaticModelCollider;

class Model : public Resource
{
  friend class ModelRenderer;
  friend class StaticModelCollider;

  void splitStringWhitespace(std::string& input, std::vector<std::string>& output);
  void splitString(std::string& input, char splitter, std::vector<std::string>& output);

  std::vector<std::sr1::shared_ptr<Part> > parts;
  std::vector<qsoft::Face> faces;

  void onLoad(std::string path);

  void processMtl(std::string path,
    std::vector<std::sr1::shared_ptr<Material> >& materials);
};
