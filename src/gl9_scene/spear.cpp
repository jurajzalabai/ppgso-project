//
// Created by juraj on 10/11/2021.
//

#include <glm/gtc/random.hpp>
#include "spear.h"
#include "projectile.h"
#include "explosion.h"
#include "seagull.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Spear::mesh;
std::unique_ptr<ppgso::Texture> Spear::texture;
std::unique_ptr<ppgso::Shader> Spear::shader;

Spear::Spear() {
    // Set random scale speed and rotation
    scale *= (1.0f);
    speed = {(0.0f), (0.0f), 0.0f};
    rotation.y = (ppgso::PI/180)*(20);
    rotation.x = (ppgso::PI/180)*(-45);

    parent = nullptr;
    child = nullptr;
//    rotMomentum = glm::ballRand(ppgso::PI);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("SpearTexture.bmp"));
//    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Spear-1.obj");
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Spear-2.obj");
}
bool Spear::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;
    std::cout<< " z spear: "<< position.z<< std::endl;
    std::cout<< " y spear: "<< position.y<< std::endl;
    std::cout<< " x spear: "<< position.x<< std::endl;
    // Animate position according to timee
    if (age > 4) {
        counter++;
        std::cout<< " frames: "<< counter<< std::endl;
        for ( auto& obj : scene.objects ) {
            // Ignore self in scene
            if (obj.get() == this)
                continue;

            // We only need to collide with asteroids, ignore other objects
            auto seagull = dynamic_cast<Seagull *>(obj.get());
            if (!seagull) continue;

            if (seagull->parent == nullptr && distance(position, seagull->position) < seagull->scale.y) {
                seagull->parent = this;
                this->child = seagull;
            }
        }
        if (this->child == nullptr) {
            position.y += 8 * dt;
            position.x -= 20 * dt;
            position.z -= 30 * dt;
            rotation.y += (-0.001f);
        }
        else if (position.y >= 2){
            position.y -= 10 * dt;
            position.x += 2 * dt;
            rotation.y += (ppgso::PI/180)*(-0.6f);
        }
//                if (position.y <= 2) {
//                    continue;
//                }
//                else {
////                    seagull->position.x = position.x;
////                    seagull->position.y = position.y;
////                    seagull->rotation.y += (-0.02f);
//                    position.y -= 10 * dt;
//                    position.x += 2 * dt;
//                    rotation.y += (-0.001f);
////                            seagull->position.x = position.x;
////                            seagull->position.y = position.y;
////                            seagull->rotation.y += (-0.02f);
////                            position.y -= 10 * dt;
////                            position.x += 2 * dt;
////                            rotation.y += (-0.001f);
//                }
//            } else {
//                position.y += 40 * dt;
//                position.x += 40 * dt;
//                rotation.y += (-0.001f);
//            }
//        }
    }

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Spear::render(Scene &scene) {
//    std::cout << age << std::endl;
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
