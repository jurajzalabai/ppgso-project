//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "particle.h"
#include "projectile.h"
#include "explosion.h"
#include "player.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Particle::mesh;
std::unique_ptr<ppgso::Texture> Particle::texture;
std::unique_ptr<ppgso::Shader> Particle::shader;

Particle::Particle(glm::vec3 p, glm::vec3 s, glm::vec3 c, float sc) {
    // Set random scale speed and rotation
    position = p;
    speed = s;
    age = 0;
    scale *= sc;
    color = c;
    fast_start = 0;
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("stars.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}
bool Particle::update(Scene &scene, float dt) {
    age += dt;
//    fast_start++;
//    speed.y = 1000 + fast_start * (10-1000);
//    speed.y -= 10 * dt;
    position += speed * dt;
    generateModelMatrix();
    return age <= 1.0;

    return true;
}

void Particle::render(Scene &scene) {
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



    // Disable depth testing
    glDisable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    // Additive blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    mesh->render();

    // Disable blending
    glDisable(GL_BLEND);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
}





