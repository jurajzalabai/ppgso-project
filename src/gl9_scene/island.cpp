//
// Created by juraj on 10/11/2021.
//

#include <glm/gtc/random.hpp>
#include "island.h"
#include "projectile.h"
#include "explosion.h"
#include "seagull.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Island::mesh;
std::unique_ptr<ppgso::Texture> Island::texture;
std::unique_ptr<ppgso::Shader> Island::shader;

Island::Island() {
    // Set random scale speed and rotation
    scale *= (1.3f);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("IslandTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Island.obj");
}
bool Island::update(Scene &scene, float dt) {

// Generate modelMatrix from position, rotation and scale
    generateModelMatrix();
//
    return true;
}

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

