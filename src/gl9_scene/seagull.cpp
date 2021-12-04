#include "seagull.h"
#include "scene.h"
#include "spear.h"

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Seagull::mesh;
std::unique_ptr<ppgso::Texture> Seagull::texture;
std::unique_ptr<ppgso::Shader> Seagull::shader;

Seagull::Seagull() {

    scale *= 3.0f;
    keyframes  = {
            {
            Keyframe(glm::vec3(25,30,10), glm::vec3((ppgso::PI/180)*(15), (ppgso::PI/180)*(-25), (ppgso::PI/180)*(-90)), 0.0f, 6.0f),
            // let cajky
            Keyframe(glm::vec3(-42,18,25), glm::vec3((ppgso::PI/180)*(15), (ppgso::PI/180)*(-25), (ppgso::PI/180)*(-90)), 0.0f, 0.0f)},

            {
            Keyframe(glm::vec3(0,0,0), glm::vec3((ppgso::PI/180)*(15), (ppgso::PI/180)*(-25), (ppgso::PI/180)*(-90)), 0.0f, 0.0f),}
    };

    if (scene_num == 1){
        if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    }
    else{
        if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    }
  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("seagullTexture.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("seagull-low-poly.obj");
}

bool Seagull::update(Scene &scene, float dt) {
  // Fire delay increment
    std::cout<<" cas: "<<age << std::endl;
    age += dt;

    if (parent == nullptr) {
        if (age >= 73.0f && age <= 75.0f) {
            position = lerp(glm::vec3{5, 6, 63}, glm::vec3(9, 3.2f, 60), age, 73.0f, 2.0f);
        }
        else if (keyframes[scene_num][curr].startTime < age) {
            if (keyframes[scene_num][curr].duration != 0) {
                if (age < keyframes[scene_num][curr].startTime + keyframes[scene_num][curr].duration){
                    position = lerp(keyframes[scene_num][curr].position, keyframes[scene_num][curr+1].position, age, keyframes[scene_num][curr].startTime, keyframes[scene_num][curr].duration);
                    rotation = lerp(keyframes[scene_num][curr].rotation, keyframes[scene_num][curr+1].rotation, age, keyframes[scene_num][curr].startTime, keyframes[scene_num][curr].duration);
                }
                else {
                    curr++;
                }
            }
        }
    }
    else {
        position = glm::vec3{0, 0, 0};
        std::cout << "salalala" << std::endl;
        if (age >= 73.0f) {
            position = glm::vec3{5, 6, 63};
            std::cout << "lalala" << position.x << position.y << position.z << std::endl;
            parent = nullptr;
        }
    }

  generateModelMatrix();
  return true;
}

void Seagull::render(Scene &scene) {
    shader->use();
    if (scene_num == 1){
        shader->setUniform("pointLights[0].position", {0,15,74});
        shader->setUniform("pointLights[0].constant", 1.0f);
        shader->setUniform("pointLights[0].linear", 0.0f);
        shader->setUniform("pointLights[0].quadratic", 0.0f);
        shader->setUniform("pointLights[0].color", {1.0f, 1.0f, 1.0f});
        shader->setUniform("pointLights[0].direction", {0.0f, -1.0f, 0.0f});
        shader->setUniform("pointLights[0].outerCutOff", glm::cos(glm::radians(80.0f)));
        shader->setUniform("pointLights[0].cutOff",  glm::cos(glm::radians(40.0f)));

        shader->setUniform("pointLights[1].position", {0,1,35});
        shader->setUniform("pointLights[1].constant", 0.7f);
        shader->setUniform("pointLights[1].linear", 0.0f);
        shader->setUniform("pointLights[1].quadratic", 0.0f);
        shader->setUniform("pointLights[1].color", {1.0f, 0.5f, 0});
        shader->setUniform("pointLights[1].direction", {0.5f, 0.5f, 0.5f});
        shader->setUniform("pointLights[1].outerCutOff", glm::cos(glm::radians(180.0f)));
        shader->setUniform("pointLights[1].cutOff",  glm::cos(glm::radians(180.0f)));

        shader->setUniform("pointLights[3].position", {8.14,5.45,62});
        shader->setUniform("pointLights[3].constant", 1.0f);
        shader->setUniform("pointLights[3].linear", 0.0f);
        shader->setUniform("pointLights[3].quadratic", 0.0f);
        shader->setUniform("pointLights[3].color", {1.0f, 1.0f, 1.0f});
        shader->setUniform("pointLights[3].direction", {0.0f, -1.0f, 0.0f});
        shader->setUniform("pointLights[3].outerCutOff", glm::cos(glm::radians(45.0f)));
        shader->setUniform("pointLights[3].cutOff",  glm::cos(glm::radians(25.0f)));

        shader->setUniform("diffuse_strength", 0.3f);
        shader->setUniform("ambient_strength", 0.2f);
        shader->setUniform("specular_strength", 0.3f);
        shader->setUniform("viewPos", scene.camera->position);
    }
    else{
        // Set up light
        shader->setUniform("LightDirection", scene.lightDirection);
    }

    // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

  // render mesh
  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("Texture", *texture);
  mesh->render();
}
