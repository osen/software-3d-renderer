#include "Component.h"

#include <qsoft/qsoft.h>

#include <sr1/zero_initialized>

class Model;
class Texture;

class ModelRenderer : public Component
{
  std::shared_ptr<Model> model;
  std::sr1::zero_initialized<float> pos;

  void onDisplay();

public:
  void onInit();
  void onInit(std::shared_ptr<Model> model);
  void setModel(std::shared_ptr<Model> model);
  std::shared_ptr<Model> getModel();

};
