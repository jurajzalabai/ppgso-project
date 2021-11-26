#include "seagull.h"
#include "scene.h"
#include "spear.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Seagull::mesh;
std::unique_ptr<ppgso::Texture> Seagull::texture;
std::unique_ptr<ppgso::Shader> Seagull::shader;

Seagull::Seagull() {

  scale *= 3.0f;
    keyframes  = {Keyframe(glm::vec3(25,30,10), glm::vec3((ppgso::PI/180)*(15), (ppgso::PI/180)*(-25), (ppgso::PI/180)*(-90)), 0.0f, 6.0f),
                  Keyframe(glm::vec3(-42,18,25), glm::vec3((ppgso::PI/180)*(15), (ppgso::PI/180)*(-25), (ppgso::PI/180)*(-90)), 0.0f, 0.0f)};
    position = keyframes[0].position;
    rotation = keyframes[0].rotation;

  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("seagullTexture.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("seagull-low-poly.obj");
}

bool Seagull::update(Scene &scene, float dt) {
  // Fire delay increment
    std::cout<<" cas: "<<age << std::endl;
    age += dt;

    if (parent == nullptr) {
        if (keyframes[curr].startTime < age) {
            if (keyframes[curr].duration != 0) {
                if (age < keyframes[curr].startTime + keyframes[curr].duration){
                    position = lerp(keyframes[curr].position, keyframes[curr+1].position, age, keyframes[curr].startTime, keyframes[curr].duration);
                    rotation = lerp(keyframes[curr].rotation, keyframes[curr+1].rotation, age, keyframes[curr].startTime, keyframes[curr].duration);
                }
                else {
                    curr++;
                }
            }
        }
    }
    else {
        position = glm::vec3{0, 0, 0};
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
