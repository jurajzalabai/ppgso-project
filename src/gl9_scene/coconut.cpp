//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "coconut.h"
#include "ocean.h"
#include "turtle.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


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
//    speed.x = 10;
//    speed.z = 0;
    rotation.x = (ppgso::PI/180)*(-90);
    rotMomentum = glm::ballRand(ppgso::PI);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("CoconutTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Coconut.obj");
}
bool Coconut::update(Scene &scene, float dt) {
    age += dt;
    if (willFall && age > 43.0f){
//        rotation += rotMomentum * dt;
        if (position.y > 0.5f){
            position.y -= 20 * dt;
            fall_time = age;
        }
        else{
            for (auto &obj : scene.objects) {
                // Ignore self in scene
                if (obj.get() == this)
                    continue;

                auto turtle = dynamic_cast<Turtle *>(obj.get());
                if (turtle) {
                    if (age - fall_time <= 3.0f) {
                        glm::vec3 new_speed = lerp(speed, glm::vec3(0, 0, 0), age, fall_time, 3.0f);
                        if(distance(position, turtle->position) > 6.0f && !collided) {
                            position += new_speed * dt;
                        }
                        else {
                            collided = true;
                            position -= new_speed * dt;
                        }
                    }
                    else {
                        willFall = false;
                    }
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

