#include <glm/gtc/random.hpp>
#include "particle.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

// Static resources
std::unique_ptr<ppgso::Mesh> Particle::mesh;
std::unique_ptr<ppgso::Texture> Particle::texture;
std::unique_ptr<ppgso::Shader> Particle::shader;

Particle::Particle(glm::vec3 p, glm::vec3 s, glm::vec3 c, float sc, bool parts) {
    position = p;
    speed = s;
    age = 0;
    scale *= sc;
    color = c;
    fast_start = 0;
    life_age = glm::linearRand(3.0f, 7.0f);
    part = parts;
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("stars.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool Particle::update(Scene &scene, float dt) {
    age += dt;
    fast_start++;
    if (color == glm::vec3(0.43f,0.02f,0.03f)){
            scale *= 0.995;
        if (!part){
            speed.x -= 10 * dt;
            speed.z -= 10 * dt;
            speed.y -= 30 * dt;
        }
    }else{
        if (speed.y >= 0 && part){
            speed.y = 4 + (fast_start / 1000) * (1 - 4);
        }
        if (!part){
            speed.y -= 20 * dt;
        }
        if (life_age - age <= 1.0){
            scale *= 0.965;
        }
    }
    position += speed * dt;
    generateModelMatrix();
    if (part){
        if (scene.scene_num != 1)
            return age <= life_age;
        else
            return age <= 0.8;
    }
    else
        if (color == glm::vec3(0.43f,0.02f,0.03f)){
            return age <= 1.0;
        }
        else {
            return age <= 0.5;
        }
}

void Particle::renderDepth(Scene &scene) {
}

void Particle::render(Scene &scene, unsigned int depthMap) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
//    shader->setUniform("Texture", *texture);
    shader->setUniform("OverallColor", color);

    if (part){
        // Enable blending
        glEnable(GL_BLEND);
        // Additive blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    }

    mesh->render();

    if(part){
        // Disable blending
        glDisable(GL_BLEND);
    }
}





