//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "ocean.h"
#include "seagull.h"

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Ocean::mesh;
std::unique_ptr<ppgso::Texture> Ocean::texture;
std::unique_ptr<ppgso::Shader> Ocean::shader;

Ocean::Ocean() {
    // Set random scale speed and rotation
    scale *= (15.0f);
    speed = {(0.0f), (0.0f), 0.0f};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("OceanTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Ocean.obj");
}
bool Ocean::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Ocean::renderDepth(Scene &scene) {
}

void Ocean::render(Scene &scene, unsigned int depthMap) {
    shader->use();

    shader->setUniform("pointLights[0].constant", 2.3f);
    shader->setUniform("pointLights[0].linear", 0.0f);
    shader->setUniform("pointLights[0].quadratic", 0.0f);

    if (age < 106.0f){
        shader->setUniform("pointLights[0].position", glm::vec3(0, 100, 0.0f));
        shader->setUniform("pointLights[0].color", glm::vec3(0.992f, 0.952f, 0.588f));
    }
    else if (age > 106.0f && age <= 118.0f){
        if (age > 116.0f && age <= 118.0f){
            shader->setUniform("pointLights[0].constant", lerp(glm::vec3{2.3f}, glm::vec3(1.0f), age, 116.0f, 2.0f).x);
        }
        shader->setUniform("pointLights[0].position", quadratic_lerp(glm::vec3(0, 100, 0.0f),glm::vec3(0, 100, -100.0f), glm::vec3(0, 10, -100.0f), age, 106.0f, 12.0f));
        shader->setUniform("pointLights[0].color", lerp(glm::vec3{0.992f, 0.952f, 0.588f}, glm::vec3(0.984f, 0.607f, 0.215f), age, 106.0f, 12.0f));
    }
    else if( age > 118.0f){
        shader->setUniform("pointLights[0].position", glm::vec3(0, -10, -140.5f));
        shader->setUniform("pointLights[0].color", glm::vec3(0.984f, 0.607f, 0.215f));
        shader->setUniform("pointLights[0].constant", lerp(glm::vec3{1.0f}, glm::vec3(0.9f), age, 118.0f, 2.0f).x);
    }

    shader->setUniform("pointLights[0].direction", {1.0f, 1.0f, 1.0f});
    shader->setUniform("pointLights[0].outerCutOff", glm::cos(glm::radians(180.0f)));
    shader->setUniform("pointLights[0].cutOff",  glm::cos(glm::radians(180.0f)));

    shader->setUniform("diffuse_strength", 0.5f);
    shader->setUniform("ambient_strength", 0.2f);
    shader->setUniform("specular_strength", 0.9f);
    shader->setUniform("viewPos", scene.camera->position);


    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}


