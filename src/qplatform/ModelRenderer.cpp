#include "ModelRenderer.h"
#include "Resources.h"
#include "Model.h"
#include "Window.h"
#include "Platform.h"
#include "Part.h"
#include "MaterialGroup.h"
#include "Texture.h"
#include "Environment.h"
#include "Transform.h"
#include "Camera.h"

void ModelRenderer::onInit() { }

void ModelRenderer::onInit(std::shared_ptr<Model> model)
{
  onInit();
  setModel(model);
}

void ModelRenderer::setModel(std::shared_ptr<Model> model)
{
  this->model = model;
}

std::shared_ptr<Model> ModelRenderer::getModel()
{
  return model;
}

void ModelRenderer::onDisplay()
{
  std::shared_ptr<qsoft::Renderer> r = getPlatform()->getWindow()->getRenderer();
  std::shared_ptr<Window> w = getWindow();
  r->setProjection(qsoft::Matrix::perspective(65.0f, (float)w->getWidth() / (float)w->getHeight(), 0.01f, 100.0f));

  std::shared_ptr<Camera> camera = getWindow()->getCurrentCamera();
  //camera.reset();

  if(!camera)
  {
    r->setView(
      qsoft::Matrix::translation(qsoft::Vector3(0, -3, 0)) *
      qsoft::Matrix::rotation(qsoft::Vector3(0, 90, 0))
    );
  }
  else
  {
    std::shared_ptr<Transform> t = camera->getTransform();
    r->setView(qsoft::Matrix::inverse(t->getModelMatrix()));
  }

/*
  r->setModel(
    qsoft::Matrix::translation(qsoft::Vector3(0, 0, 0)) *
    qsoft::Matrix::rotation(qsoft::Vector3(0, -pos, 0))
    //qsoft::Matrix::rotation(qsoft::Vector3(0, pos, 0))
    //qsoft::Matrix::rotation(qsoft::Vector3(0, 1, 0), pos)
  );
*/

  r->setModel(getTransform()->getModelMatrix());

  for(std::vector<std::shared_ptr<Part> >::iterator pit = model->parts.begin();
    pit != model->parts.end(); pit++)
  {
    for(size_t mgi = 0; mgi < (*pit)->getMaterialGroupCount(); mgi++)
    {
      std::shared_ptr<MaterialGroup> mg = (*pit)->getMaterialGroup(mgi);

      //if(!mg->texture)
      //if(mg->texture == getResources()->getDefaultTexture())
      //{
      //  continue;
      //}

      r->setTexture(*mg->texture->data);
      r->setMesh(mg->mesh);
      r->render();
    }
  }

  pos += 25.0f * getEnvironment()->getDeltaTime();
}
