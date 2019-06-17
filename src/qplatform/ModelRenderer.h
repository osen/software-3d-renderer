#include "Component.h"

#include <qsoft/qsoft.h>

#include <sr1/zero_initialized>
#include <sr1/memory>

class Model;
class Texture;

class ModelRenderer : public Component
{
  std::sr1::shared_ptr<Model> model;
  std::sr1::zero_initialized<float> pos;

  void onDisplay();

public:
  void onInit();
  void onInit(std::sr1::shared_ptr<Model> model);
  void setModel(std::sr1::shared_ptr<Model> model);
  std::sr1::shared_ptr<Model> getModel();

};
