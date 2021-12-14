#include <glm/gtc/random.hpp>
#include "seagull.h"
#include "sphere.h"
#include <shaders/scene_diffuse_vert_glsl.h>
#include <shaders/scene_diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Sphere::mesh;
std::unique_ptr<ppgso::Texture> Sphere::texture;
std::unique_ptr<ppgso::Shader> Sphere::shader;

Sphere::Sphere() {
    // Set random scale speed and rotation
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(scene_diffuse_vert_glsl, scene_diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("firetexture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}
bool Sphere::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;
    if (age > 106.0f && age <= 118.0f){
        color = lerp(glm::vec3{0.992f, 0.952f, 0.588f}, glm::vec3(0.984, 0.507, 0.115), age, 106.0f, 12.0f);
        position = quadratic_lerp(glm::vec3(0, 150, 0.0f),glm::vec3(0, 150, -140.0f), glm::vec3(0, -10, -140.0f), age, 106.0f, 12.0f);
    }
    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Sphere::renderDepth(Scene &scene) {

}

void Sphere::render(Scene &scene, unsigned int depthMap) {
    shader->use();


    shader->setUniform("pointLights[0].constant", 2.3f);
    shader->setUniform("pointLights[0].linear", 0.0f);
    shader->setUniform("pointLights[0].quadratic", 0.0f);

    if (age < 106.0f){
        shader->setUniform("pointLights[0].position", glm::vec3(0, 140, 0.0f));
        shader->setUniform("pointLights[0].color", glm::vec3(0.992f, 0.952f, 0.588f));
    }
    else if (age > 106.0f && age <= 118.0f){
        shader->setUniform("pointLights[0].position", quadratic_lerp(glm::vec3(0, 140, 0.0f),glm::vec3(0, 140, -140.5f), glm::vec3(0, -10, -140.5f), age, 106.0f, 12.0f));
        shader->setUniform("pointLights[0].color", lerp(glm::vec3{0.992f, 0.952f, 0.588f}, glm::vec3(0.984f, 0.607f, 0.215f), age, 106.0f, 12.0f));
    }
    else if( age > 118.0f && age < 120.0f){
        shader->setUniform("pointLights[0].constant", lerp(glm::vec3{2.3f}, glm::vec3(0.0f), age, 118.0f, 2.0f).x);
        shader->setUniform("pointLights[0].position", glm::vec3(0, -10, -140.5f));
        shader->setUniform("pointLights[0].color", glm::vec3(0.984f, 0.607f, 0.215f));
    }
    else if( age > 120.0f){
        shader->setUniform("pointLights[0].color", 0.0f);
    }
    shader->setUniform("pointLights[0].direction", {1.0f, 1.0f, 1.0f});
    shader->setUniform("pointLights[0].outerCutOff", glm::cos(glm::radians(180.0f)));
    shader->setUniform("pointLights[0].cutOff",  glm::cos(glm::radians(180.0f)));

    shader->setUniform("diffuse_strength", 1.0f);
    shader->setUniform("ambient_strength", 1.9f);
    shader->setUniform("specular_strength", 0.1f);
    shader->setUniform("viewPos", scene.camera->position);

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 0.1f, far_plane = 150.5f;
    //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
    lightProjection = glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, near_plane, far_plane);
    lightView = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f) * 20.0f, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
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




