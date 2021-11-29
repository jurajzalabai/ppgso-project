//
// Created by juraj on 10/11/2021.
//

#include <glm/gtc/random.hpp>
#include "spear.h"
#include "seagull.h"

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Spear::mesh;
std::unique_ptr<ppgso::Texture> Spear::texture;
std::unique_ptr<ppgso::Shader> Spear::shader;

Spear::Spear(Scene &scene) {

    scale *= (1.0f);
    keyframes  = {{Keyframe(glm::vec3(-1,5,47), glm::vec3((ppgso::PI/180)*(-45), (ppgso::PI/180)*(20), 0), 4.0f, 2.0f),
                  Keyframe(glm::vec3(-42,18,25), glm::vec3((ppgso::PI/180)*(15), (ppgso::PI/180)*(5), (ppgso::PI/180)*(-90)), 0.0f, 0.0f)},
                  {Keyframe(glm::vec3(0,6,3), glm::vec3((ppgso::PI/180)*(-45), (ppgso::PI/180)*(20), (ppgso::PI/180)*(180)), 0.0f, 0.0f)}};
    position = keyframes[scene.inside][0].position;
    rotation = keyframes[scene.inside][0].rotation;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("SpearTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Spear.obj");
}
bool Spear::update(Scene &scene, float dt) {

    age += dt;

    // Collision detection
    if (age > 5) {
        for (auto &obj : scene.objects) {
            // Ignore self in scene
            if (obj.get() == this)
                continue;

            auto seagull = dynamic_cast<Seagull *>(obj.get());
            if (!seagull) continue;

            if (seagull->parent == nullptr && distance(position, seagull->position) < seagull->scale.y) {
                seagull->parent = this;
                child = seagull;
            }
        }
    }

    if (child == nullptr) {
        if (keyframes[scene.inside][curr].startTime < age) {
            if (keyframes[scene.inside][curr].duration != 0) {
                if (age < keyframes[scene.inside][curr].startTime + keyframes[scene.inside][curr].duration){
                    position = lerp(keyframes[scene.inside][curr].position, keyframes[scene.inside][curr+1].position, age, keyframes[scene.inside][curr].startTime, keyframes[scene.inside][curr].duration);
                    rotation = lerp(keyframes[scene.inside][curr].rotation, keyframes[scene.inside][curr+1].rotation, age, keyframes[scene.inside][curr].startTime, keyframes[scene.inside][curr].duration);
                }
                else {
                    curr++;
                }
            }
        }
    }
    else if (position.y >= 2){
        position.y -= 10 * dt;
        position.x += 2 * dt;
        rotation.y += (ppgso::PI/180)*(-0.6f);
    }

    if(parent != nullptr) {
        position = glm::vec3{0, 6, 3};
        rotation = glm::vec3{(ppgso::PI/180)*(-45), (ppgso::PI/180)*(20), (ppgso::PI/180)*(180)};
    }


    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Spear::render(Scene &scene) {
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
