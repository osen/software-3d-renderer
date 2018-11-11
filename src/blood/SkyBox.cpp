#include "SkyBox.h"

void SkyBox::onInit()
{
  //model = getResources()->load<Model>("models/curuthers/curuthers");
  model = getResources()->load<Model>("models/skybox_night/skybox");
  //model = getResources()->load<Model>("models/re_hall/re_house_baked");
  modelRenderer = getEntity()->addComponent<ModelRenderer>(model);
}

void SkyBox::onTick()
{
  getTransform()->setPosition(getWindow()->getCurrentCamera()->getTransform()->getPosition());
}
