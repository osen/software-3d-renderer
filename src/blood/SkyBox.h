#include <qplatform/qplatform.h>

class SkyBox : public Component
{
  std::sr1::shared_ptr<Model> model;
  std::sr1::shared_ptr<ModelRenderer> modelRenderer;

  void onTick();

public:
  void onInit();

};
