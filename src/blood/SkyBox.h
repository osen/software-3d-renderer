#include <qplatform/qplatform.h>

class SkyBox : public Component
{
  std::shared_ptr<Model> model;
  std::shared_ptr<ModelRenderer> modelRenderer;

  void onTick();

public:
  void onInit();

};
