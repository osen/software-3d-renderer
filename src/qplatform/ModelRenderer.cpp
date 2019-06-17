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

//#define VISIBLE_HEIGHT 210
#define VISIBLE_HEIGHT 240

void ModelRenderer::onInit() { }

void ModelRenderer::onInit(std::sr1::shared_ptr<Model> model)
{
  onInit();
  setModel(model);
}

void ModelRenderer::setModel(std::sr1::shared_ptr<Model> model)
{
  this->model = model;
}

std::sr1::shared_ptr<Model> ModelRenderer::getModel()
{
  return model;
}

void ModelRenderer::onDisplay()
{
  std::sr1::shared_ptr<qsoft::Renderer> r = getPlatform()->getWindow()->getRenderer();
  std::sr1::shared_ptr<Window> w = getWindow();
  //r->setProjection(qsoft::Matrix::perspective(65.0f, (float)w->getWidth() / (float)w->getHeight(), 0.01f, 100.0f));

  r->setProjection(qsoft::Matrix::perspective(65.0f,
    (float)w->getWidth() / (float)((w->getHeight() / 240.0f) * (float)VISIBLE_HEIGHT),
    0.01f, 100.0f));

  std::sr1::shared_ptr<Camera> camera = getWindow()->getCurrentCamera();
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
    std::sr1::shared_ptr<Transform> t = camera->getTransform();
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

  for(std::vector<std::sr1::shared_ptr<Part> >::iterator pit = model->parts.begin();
    pit != model->parts.end(); pit++)
  {
    for(size_t mgi = 0; mgi < (*pit)->getMaterialGroupCount(); mgi++)
    {
      std::sr1::shared_ptr<MaterialGroup> mg = (*pit)->getMaterialGroup(mgi);

      //if(!mg->texture)
      //if(mg->texture == getResources()->getDefaultTexture())
      //{
      //  continue;
      //}

      r->setTexture(mg->texture->data);
      r->setMesh(mg->mesh);
      r->setViewport(0, 0, 320, VISIBLE_HEIGHT);
      //r->setViewport(0, 0, 320, 240);
      r->render();
      //r->setViewport(0, 0, 100, 100);
      //r->render();
      //r->setViewport(100, 100, 100, 100);
      //r->render();
    }
  }

  pos += 25.0f * getEnvironment()->getDeltaTime();
}
