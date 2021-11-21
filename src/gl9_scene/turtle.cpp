//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "turtle.h"
#include "projectile.h"
#include "explosion.h"
#include "seagull.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Turtle::mesh;
std::unique_ptr<ppgso::Texture> Turtle::texture;
std::unique_ptr<ppgso::Shader> Turtle::shader;

Turtle::Turtle() {
    scale *= (0.1f);
    speed = {(0.0f), (0.0f), 0.0f};
    rotation.y = (ppgso::PI/180)*(-80);
    rotation.x = (ppgso::PI/180)*(-90);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("TurtleTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("Turtle.obj");
}
bool Turtle::update(Scene &scene, float dt) {
    age += dt;
    if (age > 2){
        if (position.z < -10){
            position.z += 3*dt;
        }
        else{
            std::cout<<rotation.y<<std::endl;
            if (rotation.y <= -2.82743f){
                rotation.y -= (ppgso::PI/180)*(-0.5f);
            }else{
                rotation.y += (ppgso::PI/180)*(-0.5f);
            }
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





