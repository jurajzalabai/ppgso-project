#include <glm/gtc/random.hpp>
#include "seagull.h"
#include "table.h"

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Table::mesh;
std::unique_ptr<ppgso::Texture> Table::texture;
std::unique_ptr<ppgso::Shader> Table::shader;

Table::Table() {
    // Set random scale speed and rotation
    scale *= (1.0f);
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("TableTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Table.obj");
}
bool Table::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Table::render(Scene &scene) {
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
    shader->setUniform("pointLights[1].constant", 1.0f);
    shader->setUniform("pointLights[1].linear", 0.0f);
    shader->setUniform("pointLights[1].quadratic", 0.0f);
    shader->setUniform("pointLights[1].color", {1.0f, 0.5f, 0});
    shader->setUniform("pointLights[1].direction", {0.5f, 0.5f, 0.5f});
    shader->setUniform("pointLights[1].outerCutOff", glm::cos(glm::radians(180.0f)));
    shader->setUniform("pointLights[1].cutOff",  glm::cos(glm::radians(180.0f)));

    if (age >= 1.0 && age <= 3.0){
        shader->setUniform("pointLights[2].position", {0,1,35});
        shader->setUniform("pointLights[2].constant", 1.0f);
        shader->setUniform("pointLights[2].linear", 0.0f);
        shader->setUniform("pointLights[2].quadratic", 0.0f);
        shader->setUniform("pointLights[2].color", {1.0f, 0.8f, 0});
        shader->setUniform("pointLights[2].direction", {0.5f, 0.5f, 0.5f});
        shader->setUniform("pointLights[2].outerCutOff", glm::cos(glm::radians(180.0f)));
        shader->setUniform("pointLights[2].cutOff",  glm::cos(glm::radians(180.0f)));
        if (age>=2.5f){
            age = 0;
        }

    }
    else{
        shader->setUniform("pointLights[2].position", {0,1,35});
        shader->setUniform("pointLights[2].constant", 1.0f);
        shader->setUniform("pointLights[2].linear", 0.0f);
        shader->setUniform("pointLights[2].quadratic", 0.0f);
        shader->setUniform("pointLights[2].color", {1.0f, 0.5f, 0});
        shader->setUniform("pointLights[2].direction", {0.5f, 0.5f, 0.5f});
        shader->setUniform("pointLights[2].outerCutOff", glm::cos(glm::radians(180.0f)));
        shader->setUniform("pointLights[2].cutOff",  glm::cos(glm::radians(180.0f)));
    }

    shader->setUniform("pointLights[3].position", {8.14,5.45,62});
    shader->setUniform("pointLights[3].constant", 1.0f);
    shader->setUniform("pointLights[3].linear", 0.0f);
    shader->setUniform("pointLights[3].quadratic", 0.0f);
    shader->setUniform("pointLights[3].color", {1.0f, 1.0f, 1.0f});
    shader->setUniform("pointLights[3].direction", {0.0f, -1.0f, 0.0f});
    shader->setUniform("pointLights[3].outerCutOff", glm::cos(glm::radians(45.0f)));
    shader->setUniform("pointLights[3].cutOff",  glm::cos(glm::radians(25.0f)));

    shader->setUniform("diffuse_strength", 0.3f);
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




