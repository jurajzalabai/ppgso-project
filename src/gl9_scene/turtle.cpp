//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "turtle.h"
#include "seagull.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Turtle::mesh;
std::unique_ptr<ppgso::Texture> Turtle::texture;
std::unique_ptr<ppgso::Shader> Turtle::shader;

Turtle::Turtle() {
    scale *= (0.1f);
    keyframes = {
            {
            Keyframe(glm::vec3(-15,1,-30), glm::vec3((ppgso::PI/180)*(-90), (ppgso::PI/180)*(-80), 0), 30.0f, 5.0f),
            // korytnacka prichadza do zaberu
            Keyframe(glm::vec3(-8,1,-8), glm::vec3((ppgso::PI/180)*(-90), (ppgso::PI/180)*(-80), 0), 0.0f, 0.0f)},

            {},
            {Keyframe(glm::vec3(-8,1,-8), glm::vec3((ppgso::PI/180)*(-90), (ppgso::PI/180)*(-80), 0), 85.0f, 0.0f),}
    };

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("TurtleTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Turtle.obj");
}
bool Turtle::update(Scene &scene, float dt) {
    age += dt;

    if (keyframes[scene_num][curr].startTime < age) {
        if (keyframes[scene_num][curr].duration != 0) {
            if (age < keyframes[scene_num][curr].startTime + keyframes[scene_num][curr].duration) {
                position = lerp(keyframes[scene_num][curr].position, keyframes[scene_num][curr + 1].position, age,
                                keyframes[scene_num][curr].startTime, keyframes[scene_num][curr].duration);
                rotation = lerp(keyframes[scene_num][curr].rotation, keyframes[scene_num][curr + 1].rotation, age,
                                keyframes[scene_num][curr].startTime, keyframes[scene_num][curr].duration);
            } else {
                curr++;
            }
        }
        else {
            rotation.y = static_cast<float>(sin(age) + 4.14);
        }
    }

    generateModelMatrix();
    return true;
}

void Turtle::render(Scene &scene) {
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





