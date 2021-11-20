//
// Created by juraj on 10/11/2021.
//

#include <glm/gtc/random.hpp>
#include "island.h"
#include "projectile.h"
#include "explosion.h"
#include "player.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Island::mesh;
std::unique_ptr<ppgso::Texture> Island::texture;
std::unique_ptr<ppgso::Shader> Island::shader;

Island::Island() {
    // Set random scale speed and rotation
    scale *= (0.5f);
//    speed = {glm::linearRand(5.0f, 10.0f), glm::linearRand(5.0f, 10.0f), 0.0f};
//    rotation = glm::ballRand(ppgso::PI);
//    rotMomentum = glm::ballRand(ppgso::PI);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("IslandTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Island.obj");
}
bool Island::update(Scene &scene, float dt) {
    // Count time alive
//    age += dt;

    // Animate position according to timee
//    position += speed * dt;
    // Rotate the object
//    rotation += rotMomentum * dt;

//    if (age > 4) {
//        auto obj = std::make_unique<Island>();
//        obj->position = glm::vec3(-5,-5,0);
////        obj->position.x += glm::linearRand(-20.0f, 20.0f);
//        scene.objects.push_back(move(obj));
////        time = 0;
//    }



    // Delete when alive longer than 10s or out of visibility
//    if (age > 10.0f || position.y < -10) return false;

    // Collide with scene
//    for (auto &obj : scene.objects) {
//        // Ignore self in scene
//        if (obj.get() == this) continue;
//
//        // We only need to collide with asteroids and projectiles, ignore other objects
//        auto spear = dynamic_cast<Island*>(obj.get()); // dynamic_pointer_cast<Island>(obj);
//        auto projectile = dynamic_cast<Projectile*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);
//        auto player = dynamic_cast<Player*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);
//        if (!spear && !projectile) continue;

//        if (distance(position, player->position) < player->scale.y) {
//            speed = {glm::linearRand(-2.0f, 2.0f), glm::linearRand(-5.0f, -10.0f), 0.0f};
//        }
        // When colliding with other asteroids make sure the object is older than .5s
        // This prevents excessive collisions when asteroids explode.
//        if (spear && age < 0.5f) continue;

        // Compare distance to approximate size of the asteroid estimated from scale.
//        if (distance(position, obj->position) < (obj->scale.y + scale.y) * 0.7f) {
////            int pieces = 3;
//
//            // Too small to split into pieces
////            if (scale.y < 0.5) pieces = 0;
//
//            // The projectile will be destroyed
//            if (projectile) projectile->destroy();
//
//            // Generate smaller asteroids
//            //explode(scene, (obj->position + position) / 2.0f, (obj->scale + scale) / 2.0f, pieces);
//
//            // Destroy self
//            return false;
//        }
//    }
//
//    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();
//
    return true;
}

//void Island::explode(Scene &scene, glm::vec3 explosionPosition, glm::vec3 explosionScale, int pieces) {
//    // Generate explosion
//    auto explosion = std::make_unique<Explosion>();
//    explosion->position = explosionPosition;
//    explosion->scale = explosionScale;
//    explosion->speed = speed / 2.0f;
//    scene.objects.push_back(move(explosion));
//
//    // Generate smaller asteroids
//    for (int i = 0; i < pieces; i++) {
//        auto asteroid = std::make_unique<Island>();
//        asteroid->speed = speed + glm::vec3(glm::linearRand(-3.0f, 3.0f), glm::linearRand(0.0f, -5.0f), 0.0f);;
//        asteroid->position = position;
////        asteroid->rotMomentum = rotMomentum;
//        float factor = (float) pieces / 2.0f;
//        asteroid->scale = scale / factor;
//        scene.objects.push_back(move(asteroid));
//    }
//}

void Island::render(Scene &scene) {
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

//void Island::onClick(Scene &scene) {
//    std::cout << "Island clicked!" << std::endl;
//    explode(scene, position, {10.0f, 10.0f, 10.0f}, 0 );
//    age = 10000;
//}

