#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "asteroid.h"
#include "spear.h"

//bool Generator::update(Scene &scene, float dt) {
//  // Accumulate time
//  time += dt;
//
//  // Add object to scene when time reaches certain level
//    if(scene.keyboard[GLFW_KEY_C]) {
//        if (time > 1) {
//            auto obj = std::make_unique<Spear>();
//            obj->position = glm::vec3(-5,-5,0);
//        obj->position.x += glm::linearRand(-20.0f, 20.0f);
//            scene.objects.push_back(move(obj));
//            std::cout << "Spear generated";
//            time = 0;
//        }
//    }
//
//  return true;
//}

void Generator::render(Scene &scene) {
  // Generator will not be rendered
}
