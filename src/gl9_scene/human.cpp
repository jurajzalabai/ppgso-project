//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "human.h"
#include "projectile.h"
#include "explosion.h"
#include "player.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Human::mesh;
std::unique_ptr<ppgso::Texture> Human::texture;
std::unique_ptr<ppgso::Shader> Human::shader;

Human::Human() {
    // Set random scale speed and rotation
    scale *= (1.5f);
    speed = {(0.0f), (0.0f), 0.0f};
    rotation.z = (ppgso::PI/180)*(-180);
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("HumanTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Human.obj");
}
bool Human::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;
    if (age > 6.0f && age < 9.0f){
        position.x -= 10.0f * dt;
    }
    if (age > 12.0f && age < 15.0f) {
        position.x += 10.0f * dt;
    }
    generateModelMatrix();

    return true;
}

void Human::render(Scene &scene) {
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





