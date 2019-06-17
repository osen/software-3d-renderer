#include <qplatform/qplatform.h>

#include <sr1/zero_initialized>

class GameScreen : public Component
{
  std::sr1::shared_ptr<Model> model;
  std::sr1::shared_ptr<ModelRenderer> modelRenderer;
  std::sr1::shared_ptr<StaticModelCollider> smc;

  void addSprite(std::string path, Vector3 position);
  void addZombie(Vector3 position);

public:
  void onInit();

};
