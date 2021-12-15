#include "scene.h"

void Scene::update(float time) {
  camera->update(time);
  age += time;

  // Use iterator to update all objects so we can remove while iterating
  auto i = std::begin(objects);

  while (i != std::end(objects)) {
    // Update and remove from list if needed
    auto obj = i->get();
    if (!obj->update(*this, time))
      i = objects.erase(i); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      ++i;
  }
}

void Scene::render(unsigned int depthMap) {
  for ( auto& obj : objects )
    obj->render(*this, depthMap);
}

void Scene::renderDepth() {
    for ( auto& obj : objects )
        obj->renderDepth(*this);
}
