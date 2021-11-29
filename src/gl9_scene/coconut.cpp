//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "coconut.h"
#include "seagull.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Coconut::mesh;
std::unique_ptr<ppgso::Texture> Coconut::texture;
std::unique_ptr<ppgso::Shader> Coconut::shader;

Coconut::Coconut() {
    // Set random scale speed and rotation
    scale *= (4.0f);
    direction_x = glm::linearRand(-10.0f, 10.0f);
    direction_z = glm::linearRand(-10.0f, 10.0f);
    rotation = glm::ballRand(ppgso::PI);
    rotMomentum = glm::ballRand(ppgso::PI);
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("CoconutTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Coconut.obj");
}
bool Coconut::update(Scene &scene, float dt) {
    age += dt;
    if (age > 43.0f && age < 47.0f){
        rotation += rotMomentum * dt;
        if (position.y > 0.5f){
            position.y -= 20 * dt;
        }
        else{
                position.x += (direction_x * dt) / (age / 3);
                position.z += (direction_z * dt) / (age / 3);
        }
    }
    generateModelMatrix();

    return true;
}

void Coconut::render(Scene &scene) {
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

