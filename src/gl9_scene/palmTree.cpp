//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "palmTree.h"
#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>
#include <shaders/depth_vert_glsl.h>
#include <shaders/depth_frag_glsl.h>



// Static resources
std::unique_ptr<ppgso::Mesh> PalmTree::mesh;
std::unique_ptr<ppgso::Texture> PalmTree::texture;
std::unique_ptr<ppgso::Shader> PalmTree::shader;
std::unique_ptr<ppgso::Shader> PalmTree::shaderDepth;

PalmTree::PalmTree(Scene &scene) {
    // Set random scale speed and rotation
    scale *= (2.0f);
    if (scene.scene_num == 0) {
        position.x = glm::linearRand(-45.0f, -35.0f);
        position.z = glm::linearRand(-10.0f, 20.0f);
    }
    else {
        position = scene.palmTree_position;
    }
//    position.x = -35;
//    position.z = 2;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!shaderDepth) shaderDepth = std::make_unique<ppgso::Shader>(depth_vert_glsl, depth_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("PalmTreeTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("PalmBase.obj");
}
bool PalmTree::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void PalmTree::renderDepth(Scene &scene) {
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 150.5f;
    //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
    lightProjection = glm::ortho(-70.0f, 70.0f, -70.0f, 70.0f, near_plane, far_plane);
    lightView = glm::lookAt(glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;
    shaderDepth->use();
    shaderDepth->setUniform("lightSpaceMatrix", lightSpaceMatrix);
    shaderDepth->setUniform("model", modelMatrix);
    mesh->render();
}

void PalmTree::render(Scene &scene, unsigned int depthMap) {
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


    shader->setUniform("diffuse_strength", 0.25f);
    shader->setUniform("ambient_strength", 0.2f);
    shader->setUniform("specular_strength", 0.1f);
    shader->setUniform("viewPos", scene.camera->position);

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 150.5f;
    //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
    lightProjection = glm::ortho(-70.0f, 70.0f, -70.0f, 70.0f, near_plane, far_plane);
    lightView = glm::lookAt(glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;
    shader->setUniform("lightSpaceMatrix",lightSpaceMatrix);
        // use camera
        shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
        shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

        // render mesh
        shader->setUniform("ModelMatrix", modelMatrix);
        shader->setUniform("Texture", *texture);
        shader->setUniform("lightPos", glm::vec3(0.0f, 50.0f, 0.0f));
        shader->setTexture("shadowMap", (int)depthMap);

        mesh->render();
}
