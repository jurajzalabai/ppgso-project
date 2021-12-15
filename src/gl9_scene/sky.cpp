#include <glm/gtc/random.hpp>
#include "sky.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

// Static resources
std::unique_ptr<ppgso::Mesh> Sky::mesh;
std::unique_ptr<ppgso::Texture> Sky::texture;
std::unique_ptr<ppgso::Shader> Sky::shader;

Sky::Sky() {

    scale *= (20.0f);
    rotation.z = (ppgso::PI/180)*(-90);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("CoconutTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sky.obj");
}
bool Sky::update(Scene &scene, float dt) {
    age += dt;
    if (age > 106.0f && age <= 116.0f){
        color = lerp(glm::vec3{0.541f, 0.796f, 0.898f}, glm::vec3(0.11f,0.23f,0.42f), age, 106.0f, 10.0f);
    }
    else if( age > 116.0f && age < 120.0f){
        color = lerp(glm::vec3{0.11f,0.23f,0.42f}, glm::vec3(0.04f,0.12f,0.24f), age, 116.0f, 4.0f);
    }
    else if( age > 120.0f){
        color = lerp(glm::vec3{0.04f,0.12f,0.24f}, glm::vec3(0.02f,0.07f,0.16f), age, 120.0f, 4.0f);
    }
    generateModelMatrix();

    return true;
}

void Sky::renderDepth(Scene &scene) {
}

void Sky::render(Scene &scene, unsigned int depthMap) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    shader->setUniform("OverallColor", color);
    mesh->render();
}
