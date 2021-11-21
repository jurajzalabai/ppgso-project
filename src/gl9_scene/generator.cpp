#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "particle.h"
#include "spear.h"

bool Generator::update(Scene &scene, float dt) {
  // Accumulate time
  time += dt;

  // Add object to scene when time reaches certain level

//  if (time > 1 && time < 1.1)
//  for (int i=0; i < 20; i++ ){
//      auto obj = std::make_unique<Particle>(
//                    glm::vec3(0,10,70),
////                    glm::vec3(glm::linearRand(-2.0f, 2.0f),glm::linearRand(2.0f, 4.0f), glm::linearRand(-2.0f, 2.0f)),
//                    glm::vec3(glm::linearRand(-12.0f, -6.0f),glm::linearRand(2.0f, 4.0f), glm::linearRand(-12.0f, -6.0f)),
//                    glm::vec3(1, 0, 0));
//            scene.objects.push_back(move(obj));
//            if (i==4){
//                time = 0;
//            }
//  }
//if (time > 0.001){
            float color = glm::linearRand(0.01f, 0.05f);
            auto obj = std::make_unique<Particle>(
                    glm::vec3(62,22,9),
                    glm::vec3(glm::linearRand(-2.0f, 2.0f),glm::linearRand(4.0f, 8.0f), glm::linearRand(-2.0f, 2.0f)),
                    glm::vec3(color, color, color),
                    glm::linearRand(0.5f, 1.5f));
            scene.objects.push_back(move(obj));
            time = 0;
//}

  return true;
}

void Generator::render(Scene &scene) {
  // Generator will not be rendered
}
