//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "human.h"
#include "boots.h"

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Boots::mesh;
std::unique_ptr<ppgso::Texture> Boots::texture;
std::unique_ptr<ppgso::Shader> Boots::shader;

Boots::Boots() {


    scale *= (4.0f);
    keyframes  = {
            {
                    Keyframe(glm::vec3(-1,-1,50), glm::vec3(0, 0, (ppgso::PI/180)*(-180)), 8.0f, 3.0f),
                    //idem si po cajku
                    Keyframe(glm::vec3(-42,0,25), glm::vec3(0, 0, (ppgso::PI/180)*(-180)), 12.0f, 1.0f),
                    //otocim sa ku domu
                    Keyframe(glm::vec3(-42,0,25), glm::vec3(0, 0, (ppgso::PI/180)*(-230)), 13.0f, 5.0f),
                    //idem domov
                    Keyframe(glm::vec3(25,0,0), glm::vec3(0, 0, (ppgso::PI/180)*(-230)), 0.0f, 0.0f)},


            {
                    Keyframe(glm::vec3(0,0.4,90), glm::vec3(0, 0, (ppgso::PI/180)*(-180)), 60.0f, 3.0f),
                    // prichod ku krbu
                    Keyframe(glm::vec3(-5,0.4,41), glm::vec3(0, 0, (ppgso::PI/180)*(-180)), 63.0f, 2.0f),
                    // otocenie ku krbu
                    Keyframe(glm::vec3(-5,0.4,41), glm::vec3(0, 0, (ppgso::PI/180)*(-220)), 72.0f, 1.0f),
                    // otocenie ku stolu
                    Keyframe(glm::vec3(-5,0.4,41), glm::vec3(0, 0, (ppgso::PI/180)*(-300)), 73.0f, 4.0f),
                    // prichod ku stolu
                    Keyframe(glm::vec3(5,0.4,60), glm::vec3(0, 0, (ppgso::PI/180)*(-300)), 0.0f, 0.0f)}
    };

    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);

    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("stars.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("boots.obj");
}
bool Boots::update(Scene &scene, float dt) {
    age += dt;
//    std::cout << scene_num << curr << "age human:" << age << std::endl;
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
    }
    generateModelMatrix();

    return true;
}

void Boots::render(Scene &scene) {
    shader->use();

    if (scene_num == 1){
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

        shader->setUniform("diffuse_strength", 0.3f);
        shader->setUniform("ambient_strength", 0.2f);
        shader->setUniform("specular_strength", 0.3f);
        shader->setUniform("viewPos", scene.camera->position);
    }
    else{
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
    }


    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}





