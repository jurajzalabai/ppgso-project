//
// Created by juraj on 10/11/2021.
//

#include <glm/gtc/random.hpp>
#include "spear.h"
#include "projectile.h"
#include "explosion.h"
#include "player.h"

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
    rotation.y = (ppgso::PI/180)*(-60);
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
            auto player = dynamic_cast<Player *>(obj.get());
            if (!player) continue;

            if (distance(position, player->position) < player->scale.y) {
                // Explode
//        spear->position.x -= 2;
//        spear->position.y -= 2;
//        rotation.y = (ppgso::PI/180)*(-60);
                if (position.y <= 2) {

                } else {
                    player->position.x = position.x;
                    player->position.y = position.y;
                    player->rotation.y += (-0.02f);
                    position.y -= 10 * dt;
                    position.x += 2 * dt;
                    rotation.y += (-0.001f);
                }
            } else {
                position.y += 40 * dt;
                position.x += 40 * dt;
                rotation.y += (-0.001f);
            }
        }
    }

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Spear::explode(Scene &scene, glm::vec3 explosionPosition, glm::vec3 explosionScale, int pieces) {
    // Generate explosion
    auto explosion = std::make_unique<Explosion>();
    explosion->position = explosionPosition;
    explosion->scale = explosionScale;
    explosion->speed = speed / 2.0f;
    scene.objects.push_back(move(explosion));

    // Generate smaller asteroids
    for (int i = 0; i < pieces; i++) {
        auto asteroid = std::make_unique<Spear>();
        asteroid->speed = speed + glm::vec3(glm::linearRand(-3.0f, 3.0f), glm::linearRand(0.0f, -5.0f), 0.0f);;
        asteroid->position = position;
//        asteroid->rotMomentum = rotMomentum;
        float factor = (float) pieces / 2.0f;
        asteroid->scale = scale / factor;
        scene.objects.push_back(move(asteroid));
    }
}

void Spear::render(Scene &scene) {
//    std::cout << age << std::endl;
    if (age > 4){
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
}

void Spear::onClick(Scene &scene) {
    std::cout << "Spear clicked!" << std::endl;
    explode(scene, position, {10.0f, 10.0f, 10.0f}, 0 );
    age = 10000;
}

