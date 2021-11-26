//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "palmTree.h"
#include "seagull.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> PalmTree::mesh;
std::unique_ptr<ppgso::Texture> PalmTree::texture;
std::unique_ptr<ppgso::Shader> PalmTree::shader;

PalmTree::PalmTree() {
    // Set random scale speed and rotation
    scale *= (2.0f);
    speed = {(0.0f), (0.0f), 0.0f};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("PalmTreeTexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("PalmTree.obj");
}
bool PalmTree::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void PalmTree::render(Scene &scene) {
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
