#include <glm/gtc/random.hpp>
#include "seagull.h"
#include "lamp.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Lamp::mesh;
std::unique_ptr<ppgso::Texture> Lamp::texture;
std::unique_ptr<ppgso::Shader> Lamp::shader;

Lamp::Lamp() {
    // Set random scale speed and rotation
    scale *= (0.1f);
    speed = {(0.0f), (0.0f), 0.0f};
    this->age = age;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("PlateTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Lamp.obj");
}
bool Lamp::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Lamp::render(Scene &scene) {
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






