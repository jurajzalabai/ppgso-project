#include <glm/gtc/random.hpp>
#include "fireplace.h"

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Fireplace::mesh;
std::unique_ptr<ppgso::Texture> Fireplace::texture;
std::unique_ptr<ppgso::Shader> Fireplace::shader;

Fireplace::Fireplace() {
    // Set scale
    scale *= (0.1f);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("FireplaceTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Fireplace.obj");
}
bool Fireplace::update(Scene &scene, float dt) {

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Fireplace::renderDepth(Scene &scene) {
}

void Fireplace::render(Scene &scene, unsigned int depthMap) {
    shader->use();
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

    shader->setUniform("diffuse_strength", 0.9f);
    shader->setUniform("ambient_strength", 0.2f);
    shader->setUniform("specular_strength", 0.3f);
    shader->setUniform("viewPos", scene.camera->position);


    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}


