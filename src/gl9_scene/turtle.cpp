#include <glm/gtc/random.hpp>
#include "turtle.h"
#include "particle.h"

#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>
#include <shaders/depth_vert_glsl.h>
#include <shaders/depth_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Turtle::mesh;
std::unique_ptr<ppgso::Texture> Turtle::texture;
std::unique_ptr<ppgso::Shader> Turtle::shader;
std::unique_ptr<ppgso::Shader> Turtle::shaderDepth;

Turtle::Turtle() {
    scale *= (0.1f);
    keyframes = {
            {
            Keyframe(glm::vec3(-15,1,-30), glm::vec3((ppgso::PI/180)*(-90), (ppgso::PI/180)*(-80), 0), 30.0f, 5.0f),
            // korytnacka prichadza do zaberu
            Keyframe(glm::vec3(-8,1,-8), glm::vec3((ppgso::PI/180)*(-90), (ppgso::PI/180)*(-80), 0), 0.0f, 0.0f)},

            {},
            {Keyframe(glm::vec3(-8,1,-8), glm::vec3((ppgso::PI/180)*(-90), (ppgso::PI/180)*(-80), 0), 98.0f, 2.0f),
             // otoci sa k moru
             Keyframe(glm::vec3(-8,1,-8), glm::vec3((ppgso::PI/180)*(-90), (ppgso::PI/180)*(110), 0), 100.0f, 5.0f),
             // prichadza k moru
             Keyframe(glm::vec3(-20,0.000579834,-48.949), glm::vec3((ppgso::PI/180)*(-90), (ppgso::PI/180)*(110), 0), 105.0f, 2.0f),
             // ponori sa
             Keyframe(glm::vec3(-22,-4,-58.949), glm::vec3((ppgso::PI/180)*(-90), (ppgso::PI/180)*(110), 0), 0.0f, 0.0f),
             }
    };

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!shaderDepth) shaderDepth = std::make_unique<ppgso::Shader>(depth_vert_glsl, depth_frag_glsl);
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
        else if (age < 98.0f){
            rotation.y = static_cast<float>(sin(age) + 4.14);
        }
    }
    else if (scene_num == 2){
        rotation.y = static_cast<float>(sin(age) + 4.14);
    }

    generateModelMatrix();
    return true;
}

void Turtle::renderDepth(Scene &scene) {
}

void Turtle::render(Scene &scene, unsigned int depthMap) {
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

    shader->setUniform("diffuse_strength", 0.4f);
    shader->setUniform("ambient_strength", 0.2f);
    shader->setUniform("specular_strength", 0.4f);
    shader->setUniform("viewPos", scene.camera->position);

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 150.5f;
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





