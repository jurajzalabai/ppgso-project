//
// Created by juraj on 10/11/2021.
//

#include <glm/gtc/random.hpp>
#include "spear.h"
#include "seagull.h"
#include "particle.h"

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Spear::mesh;
std::unique_ptr<ppgso::Texture> Spear::texture;
std::unique_ptr<ppgso::Shader> Spear::shader;

Spear::Spear() {

    scale *= (1.0f);
    keyframes  = {
            {
            Keyframe(glm::vec3(-1,5,47), glm::vec3((ppgso::PI/180)*(-45), (ppgso::PI/180)*(20), 0), 4.0f, 2.0f),
            // trafenie cajky
            Keyframe(glm::vec3(-22,18,25), glm::vec3((ppgso::PI/180)*(15), (ppgso::PI/180)*(5), (ppgso::PI/180)*(-90)), 0.0f, 0.0f)},

            {
            Keyframe(glm::vec3(0,6,3), glm::vec3((ppgso::PI/180)*(-45), (ppgso::PI/180)*(20), (ppgso::PI/180)*(180)), 0.0f, 0.0f)}
    };

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("SpearTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Spear.obj");
}
bool Spear::update(Scene &scene, float dt) {

    age += dt;

    // Collision detection
    if (age > 5 && child == nullptr) {
        for (auto &obj : scene.objects) {
            // Ignore self in scene
            if (obj.get() == this)
                continue;

            auto seagull = dynamic_cast<Seagull *>(obj.get());
            if (!seagull) continue;

            if ((seagull->parent == nullptr && distance(position, seagull->position) < seagull->scale.y) || scene_num == 1) {
                for (int i = 0; i<100; i++) {
                    auto obj2 = std::make_unique<Particle>(
                            glm::vec3(position),
                            glm::vec3(glm::linearRand(-3.0f, 3.0f), glm::linearRand(-5.0f, -4.0f),
                                      glm::linearRand(-10.0f, -5.0f)),
                            glm::vec3(0.43f,0.02f,0.03f),
                            glm::linearRand(0.07f, 0.11f), false);
                    scene.objects.push_back(move(obj2));
                }
                seagull->parent = this;
                child = seagull;
            }
        }
    }

    if (child == nullptr) {
        if (keyframes[scene_num][curr].startTime < age) {
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

    else if (position.y >= 0 && age > 6.0f && age < 8.0f){
        position += (gravity + (dynamic_cast<Seagull *>(child))->flight ) * dt;
        rotation.y += (ppgso::PI/180)*(300)*dt;
        fall_time = age;
    }
    else{
        if (fall_time < age && fall_time + 0.2 > age){
            for (int i = 0; i<30; i++) {
                auto obj2 = std::make_unique<Particle>(
                        glm::vec3(position),
                        glm::vec3(glm::linearRand(-6.0f, 6.0f), glm::linearRand(2.0f, 3.0f),
                                  glm::linearRand(-6.0f, 6.0f)),
                        glm::vec3(0.902, 0.900, 0.50),
                        glm::linearRand(0.1f, 0.2f), false);
                scene.objects.push_back(move(obj2));
                if (i==29){
                    fall_time = 0;
                }
            }
        }
    }

    if(parent != nullptr) {
        if (age < 55.0f) {
            position = glm::vec3{0, 6, 3};
            rotation = glm::vec3{(ppgso::PI/180)*(-45), (ppgso::PI/180)*(20), (ppgso::PI/180)*(180)};
        } else if (age < 72.0f) {
            if (age < 63.0f) {
                position = glm::vec3{0, 6, 3};
                rotation = glm::vec3{(ppgso::PI / 180) * (-45), (ppgso::PI / 180) * (20), (ppgso::PI / 180) * (180)};
            } else if (age > 63.0f && age < 65.0f) {
                position = lerp(glm::vec3{0, 6, 3}, glm::vec3{0.1, 1.7, 4}, age, 63.0f, 2.0f);
                rotation = lerp(glm::vec3{(ppgso::PI / 180) * (-45), (ppgso::PI / 180) * (20), (ppgso::PI / 180) * (180)},
                                glm::vec3{(ppgso::PI / 180) * (-105), (ppgso::PI / 180) * (20), (ppgso::PI / 180) * (180)},
                                age, 63.0f, 2.0f);
            } else if (age > 70.0f && age < 72.0f){
                position = lerp(glm::vec3{0.1, 1.7, 4}, glm::vec3{0, 6, 3}, age, 70.0f, 2.0f);
                rotation = lerp(glm::vec3{(ppgso::PI / 180) * (-105), (ppgso::PI / 180) * (20), (ppgso::PI / 180) * (180)},
                                glm::vec3{(ppgso::PI / 180) * (-45), (ppgso::PI / 180) * (20), (ppgso::PI / 180) * (180)},
                                age, 70.0f, 2.0f);
            }
        }
    }

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Spear::renderDepth(Scene &scene) {
}

void Spear::render(Scene &scene, unsigned int depthMap) {
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
        shader->setUniform("pointLights[1].constant", 0.8f);
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
        shader->setUniform("pointLights[0].constant", 2.3f);
        shader->setUniform("pointLights[0].linear", 0.0f);
        shader->setUniform("pointLights[0].quadratic", 0.0f);

        if (age < 84.0f){
            shader->setUniform("pointLights[0].position", glm::vec3(0, 100, 0.0f));
            shader->setUniform("pointLights[0].color", glm::vec3(0.992f, 0.952f, 0.588f));
        }
        else if (age > 84.0f && age <= 96.0f){
            shader->setUniform("pointLights[0].position", quadratic_lerp(glm::vec3(0, 100, 0.0f),glm::vec3(0, 100, -100.0f), glm::vec3(0, 10, -100.0f), age, 84.0f, 12.0f));
            shader->setUniform("pointLights[0].color", lerp(glm::vec3{0.992f, 0.952f, 0.588f}, glm::vec3(0.984f, 0.607f, 0.215f), age, 84.0f, 12.0f));
        }
        else if( age > 96.0f){
            shader->setUniform("pointLights[0].position", glm::vec3(0, 10, -100.0f));
            shader->setUniform("pointLights[0].color", glm::vec3(0.984f, 0.607f, 0.215f));
        }
        shader->setUniform("pointLights[0].direction", {1.0f, 1.0f, 1.0f});
        shader->setUniform("pointLights[0].outerCutOff", glm::cos(glm::radians(180.0f)));
        shader->setUniform("pointLights[0].cutOff",  glm::cos(glm::radians(180.0f)));

        shader->setUniform("diffuse_strength", 0.25f);
        shader->setUniform("ambient_strength", 0.2f);
        shader->setUniform("specular_strength", 0.1f);
        shader->setUniform("viewPos", scene.camera->position);
    }


    // use camera
        shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
        shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

        // render mesh
        shader->setUniform("ModelMatrix", modelMatrix);
        shader->setUniform("Texture", *texture);
        mesh->render();
}
