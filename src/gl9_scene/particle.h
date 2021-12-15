#pragma once
#include <memory>

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"

class Particle final : public Object {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    float age{0.0f};
    float life_age{0.0f};
    float fast_start{0.0f};
    glm::vec3 speed;
    glm::vec3 color;
    bool part;


public:

    Particle(glm::vec3 p, glm::vec3 s, glm::vec3 c, float sc, bool parts);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene, unsigned int depthMap) override;

    void renderDepth(Scene &scene) override;

private:
};
