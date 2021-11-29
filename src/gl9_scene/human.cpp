//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "human.h"
#include "spear.h"

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Human::mesh;
std::unique_ptr<ppgso::Texture> Human::texture;
std::unique_ptr<ppgso::Shader> Human::shader;

Human::Human() {

    scale *= (4.0f);

    keyframes  = {Keyframe(glm::vec3(-1,-1,50), glm::vec3(0, 0, (ppgso::PI/180)*(-180)), 8.0f, 3.0f),
                  Keyframe(glm::vec3(-42,0,25), glm::vec3(0, 0, (ppgso::PI/180)*(-180)), 12.0f, 1.0f),
                  Keyframe(glm::vec3(-42,0,25), glm::vec3(0, 0, (ppgso::PI/180)*(-230)), 13.0f, 5.0f),
                  Keyframe(glm::vec3(22,0,0), glm::vec3(0, 0, (ppgso::PI/180)*(-230)), 0.0f, 0.0f)};

    position = keyframes[0].position;
    rotation = keyframes[0].rotation;

    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("HumanTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Human.obj");
}
bool Human::update(Scene &scene, float dt) {
    age += dt;

    if (scene.name){
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

        if(curr == 1 && child == nullptr) {
            for (auto &obj : scene.objects) {

                if (obj.get() == this)
                    continue;

                auto spear = dynamic_cast<Spear *>(obj.get());
                if (!spear) continue;

                spear->parent = this;
                child = spear;
            }
        }
    }
    else{
    }

    generateModelMatrix();

    return true;
}

void Human::render(Scene &scene) {
    shader->use();
    shader->setUniform("pointLights[0].position", {0,15,74});
    shader->setUniform("pointLights[0].constant", 1.0f);
    shader->setUniform("pointLights[0].linear", 0.0f);
    shader->setUniform("pointLights[0].quadratic", 0.0f);
    shader->setUniform("pointLights[0].color", {1.0f, 1.0f, 1.0f});
    shader->setUniform("pointLights[0].direction", {0.0f, -1.0f, 0.0f});
    shader->setUniform("pointLights[0].outerCutOff", glm::cos(glm::radians(80.0f)));
    shader->setUniform("pointLights[0].cutOff",  glm::cos(glm::radians(40.0f)));

    shader->setUniform("pointLights[1].position", {0,1,35});
    shader->setUniform("pointLights[1].constant", 1.0f);
    shader->setUniform("pointLights[1].linear", 0.0f);
    shader->setUniform("pointLights[1].quadratic", 0.0f);
    shader->setUniform("pointLights[1].color", {1.0f, 0.5f, 0});
    shader->setUniform("pointLights[1].direction", {0.5f, 0.5f, 0.5f});
    shader->setUniform("pointLights[1].outerCutOff", glm::cos(glm::radians(180.0f)));
    shader->setUniform("pointLights[1].cutOff",  glm::cos(glm::radians(180.0f)));

    shader->setUniform("diffuse_strength", 0.3f);
    shader->setUniform("ambient_strength", 0.2f);
    shader->setUniform("specular_strength", 0.3f);
    shader->setUniform("viewPos", scene.camera->position);



    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}





