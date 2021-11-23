#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "particle.h"
#include "spear.h"

bool Generator::update(Scene &scene, float dt) {
  // Accumulate time
  time += dt;
  time_sand += dt;

  // Add object to scene when time reaches certain level

      if (time_sand > 2 && time_sand < 2.2)
      for (int i=0; i < 50; i++ ){
          auto obj2 = std::make_unique<Particle>(
                        glm::vec3(-15,1,-10),
    //                    glm::vec3(glm::linearRand(-2.0f, 2.0f),glm::linearRand(2.0f, 4.0f), glm::linearRand(-2.0f, 2.0f)),
                        glm::vec3(glm::linearRand(-15.0f, 15.0f),glm::linearRand(2.0f, 3.0f), glm::linearRand(-15.0f, 15.0f)),
                        glm::vec3(0.7, 0.6, 0.1),
                        glm::linearRand(0.2f, 0.5f), false);
                scene.objects.push_back(move(obj2));
                if (i==49){
                    time_sand = 0;
                }
      }
//if (time > 0.001){
            float color = glm::linearRand(0.01f, 0.05f);
            auto obj = std::make_unique<Particle>(
                    glm::vec3(62,22,9),
                    glm::vec3(glm::linearRand(-2.0f, 2.0f),glm::linearRand(4.0f, 8.0f), glm::linearRand(-2.0f, 2.0f)),
                    glm::vec3(color, color, color),
                    glm::linearRand(0.5f, 1.5f), true);
            scene.objects.push_back(move(obj));
            time = 0;
//}

  return true;
}

void Generator::render(Scene &scene) {
  // Generator will not be rendered
}
