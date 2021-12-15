#include "scene.h"
//#include "spear.h"

void Scene::update(float time) {
  camera->update(time);
  age += time;
//  if (camera->position.x >= 20){
//      auto spear = std::make_unique<Spear>();
//      spear->position = glm::vec3(camera->position.x,-10,0);
//      objects.push_back(move(spear));
//  }
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
  // Simply render all objects
  for ( auto& obj : objects )
    obj->render(*this, depthMap);
}

void Scene::renderDepth() {
    // Simply render all objects
    for ( auto& obj : objects )
        obj->renderDepth(*this);
}

std::vector<Object*> Scene::intersect(const glm::vec3 &position, const glm::vec3 &direction) {
  std::vector<Object*> intersected = {};
  for(auto& object : objects) {
    // Collision with sphere of size object->scale.x
    auto oc = position - object->position;
    auto radius = object->scale.x;
    auto a = glm::dot(direction, direction);
    auto b = glm::dot(oc, direction);
    auto c = glm::dot(oc, oc) - radius * radius;
    auto dis = b * b - a * c;

    if (dis > 0) {
      auto e = sqrt(dis);
      auto t = (-b - e) / a;

      if ( t > 0 ) {
        intersected.push_back(object.get());
        continue;
      }

      t = (-b + e) / a;

      if ( t > 0 ) {
        intersected.push_back(object.get());
        continue;
      }
    }
  }

  return intersected;
}
