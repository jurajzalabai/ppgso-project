#include "seagull.h"
#include "scene.h"
#include "asteroid.h"
#include "projectile.h"
#include "explosion.h"
#include "spear.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Seagull::mesh;
std::unique_ptr<ppgso::Texture> Seagull::texture;
std::unique_ptr<ppgso::Shader> Seagull::shader;

Seagull::Seagull() {
  // Scale the default model
  scale *= 3.0f;
  rotation.z = ppgso::PI/-2.0f;
  rotation.x = (ppgso::PI/180.0f)*(15);;
  rotation.y = (ppgso::PI/180.0f)*(-25);

  parent = nullptr;
  child = nullptr;

  // Initialize static resources if needed
  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("seagullTexture.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("seagull-low-poly.obj");
}

bool Seagull::update(Scene &scene, float dt) {
  // Fire delay increment
    std::cout<<" cas: "<<age << std::endl;
  age += dt;

    for ( auto& obj : scene.objects ) {
        if (obj.get() == this)
            continue;

        // We only need to collide with asteroids, ignore other objects
        auto spear = dynamic_cast<Spear *>(obj.get());
        if (!spear) continue;

        if (parent == nullptr) {
            position.x -= 10 * dt;
            position.y -= 2 * dt;
        }
        else {
            (*parent).update(scene, dt);
            position = glm::vec3{0, 0, 0};
        }

    }

  generateModelMatrix();
  return true;
}

void Seagull::render(Scene &scene) {
  shader->use();

  // Set up light
  shader->setUniform("LightDirection", scene.lightDirection);

  // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

  // render mesh
  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("Texture", *texture);
  mesh->render();
}
