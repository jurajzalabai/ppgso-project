//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "coconut.h"
#include "ocean.h"
#include <random>

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Coconut::mesh;
std::unique_ptr<ppgso::Texture> Coconut::texture;
std::unique_ptr<ppgso::Shader> Coconut::shader;

Coconut::Coconut() {
    // Set random scale speed and rotation
    scale *= (4.0f);
//    rotation = glm::ballRand(ppgso::PI);
    speed.x = glm::linearRand(-10.0f, 10.0f);
    speed.z = glm::linearRand(0.0f, 10.0f);
    rotation.x = (ppgso::PI/180)*(-90);
    rotMomentum = glm::ballRand(ppgso::PI);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("CoconutTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Coconut.obj");
}
bool Coconut::update(Scene &scene, float dt) {
    age += dt;
    if (willFall && age > 43.0f){
//        rotation += rotMomentum * dt;
        if (position.y > 0.5f){
            position.y -= 20 * dt;
        }
        else{
//                position.x += (direction_x * dt) / (age / 3);
//                position.z += (direction_z * dt) / (age / 3);
            position.x += speed.x * dt;
            position.z += speed.z * dt;
            for (auto &obj : scene.objects) {
                // Ignore self in scene
                if (obj.get() == this)
                    continue;

                auto object = dynamic_cast<Object *>(obj.get());

                if (distance(position, object->position) < object->scale.y) {
                    speed = glm::vec3(0, 0,0 );
                }
            }
        }
    }
    generateModelMatrix();

    return true;
}

void Coconut::render(Scene &scene) {
//    std::cout << age << std::endl;
    shader->use();

    shader->setUniform("pointLights[0].constant", 2.3f);
    shader->setUniform("pointLights[0].linear", 0.0f);
    shader->setUniform("pointLights[0].quadratic", 0.0f);

    if (age < 84.0f){
        shader->setUniform("pointLights[0].position", glm::vec3(0, 100, 0.0f));
        shader->setUniform("pointLights[0].color", glm::vec3(0.992f, 0.952f, 0.588f));
    }
    else if (age > 84.0f && age <= 96.0f){
        shader->setUniform("pointLights[0].position", quadratic_lerp(glm::vec3(0, 100, 0.0f),glm::vec3(0, 100, -100.0f), glm::vec3(0, 10, -100.0f), age, 84.0f, 12.0f));
        shader->setUniform("pointLights[0].color", lerp(glm::vec3{0.992f, 0.952f, 0.588f}, glm::vec3(0.984f, 0.607f, 0.215f), age, 84.0f, 12.0f));
    }
    else if( age > 96.0f){
        shader->setUniform("pointLights[0].position", glm::vec3(0, 10, -100.0f));
        shader->setUniform("pointLights[0].color", glm::vec3(0.984f, 0.607f, 0.215f));
    }
    shader->setUniform("pointLights[0].direction", {1.0f, 1.0f, 1.0f});
    shader->setUniform("pointLights[0].outerCutOff", glm::cos(glm::radians(180.0f)));
    shader->setUniform("pointLights[0].cutOff",  glm::cos(glm::radians(180.0f)));

    shader->setUniform("diffuse_strength", 0.25f);
    shader->setUniform("ambient_strength", 0.2f);
    shader->setUniform("specular_strength", 0.1f);
    shader->setUniform("viewPos", scene.camera->position);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}

