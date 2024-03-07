#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"
#include "components/physics_component.h"
#include "components/render_component.h"
#include "components/transform_component.h"

#include "factories/factory.h"

int main() {

  App *app = new App();
  Factory *factory = new Factory(app->physicsComponents, app->renderComponents,
                                 app->transformComponents);

  // position of the object
  // rotation of the object
  factory->make_obj({4.0f, 2.0f, 0.25f}, {1.0f, 0.0f, 180.0f});

  unsigned int cameraEntity =
      factory->make_camera({0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f});

  CameraComponent *camera = new CameraComponent();
  app->cameraComponent = camera;
  app->cameraID = cameraEntity;

  app->set_up_opengl();
  app->make_systems();

  app->run();

  delete factory;
  delete app;
  return 0;
}