#include <glm/gtc/random.hpp>
#include "seagull.h"
#include "sphere.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Sphere::mesh;
std::unique_ptr<ppgso::Texture> Sphere::texture;
std::unique_ptr<ppgso::Shader> Sphere::shader;

Sphere::Sphere() {
    // Set random scale speed and rotation
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sphere.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}
bool Sphere::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;
    if (age > 106.0f && age <= 118.0f){
        color = lerp(glm::vec3{0.992f, 0.952f, 0.588f}, glm::vec3(0.984, 0.507, 0.115), age, 106.0f, 12.0f);
        position = quadratic_lerp(glm::vec3(0, 100, 0.0f),glm::vec3(0, 100, -100.0f), glm::vec3(0, 10, -100.0f), age, 106.0f, 12.0f);
    }
    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Sphere::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
//    shader->setUniform("Texture", *texture);
    shader->setUniform("OverallColor", color);
    mesh->render();
}




