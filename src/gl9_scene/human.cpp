//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "human.h"
#include "spear.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Human::mesh;
std::unique_ptr<ppgso::Texture> Human::texture;
std::unique_ptr<ppgso::Shader> Human::shader;

Human::Human() {

    scale *= (4.0f);

    keyframes  = {Keyframe(glm::vec3(-1,-1,50), glm::vec3(0, 0, (ppgso::PI/180)*(-180)), 8.0f, 3.0f),
                  Keyframe(glm::vec3(-42,0,25), glm::vec3(0, 0, (ppgso::PI/180)*(-180)), 12.0f, 1.0f),
                  Keyframe(glm::vec3(-42,0,25), glm::vec3(0, 0, (ppgso::PI/180)*(-230)), 13.0f, 5.0f),
                  Keyframe(glm::vec3(22,0,0), glm::vec3(0, 0, (ppgso::PI/180)*(-230)), 0.0f, 0.0f)};

    position = keyframes[0].position;
    rotation = keyframes[0].rotation;

    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("HumanTexture-1.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Human-1.obj");
}
bool Human::update(Scene &scene, float dt) {
    age += dt;

    if (keyframes[curr].startTime < age) {
        if (keyframes[curr].duration != 0) {
            if (age < keyframes[curr].startTime + keyframes[curr].duration){
                position = lerp(keyframes[curr].position, keyframes[curr+1].position, age, keyframes[curr].startTime, keyframes[curr].duration);
                rotation = lerp(keyframes[curr].rotation, keyframes[curr+1].rotation, age, keyframes[curr].startTime, keyframes[curr].duration);
            }
            else {
                curr++;
            }
        }
    }

    if(curr == 1 && child == nullptr) {
        for (auto &obj : scene.objects) {

            if (obj.get() == this)
                continue;

            auto spear = dynamic_cast<Spear *>(obj.get());
            if (!spear) continue;

            spear->parent = this;
            child = spear;
        }
    }

    generateModelMatrix();

    return true;
}

void Human::render(Scene &scene) {
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





