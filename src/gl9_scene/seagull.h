#pragma once
#include <ppgso/ppgso.h>

#include "object.h"

class Seagull final : public Object {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    unsigned long long int curr = 0;

public:

    float age{0.0f};
    int scene_num = -1;
    glm::vec3 flight = glm::vec3(-7.0f, 0, 2.5f);
    glm::vec3 wind = glm::vec3(-0.833f, 0, 0);
    glm::vec3 lift = glm::vec3(0, 7.81f, 0);
    glm::vec3 gravity = glm::vec3(0, -9.81f, 0);

    Seagull();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene, unsigned int depthMap) override;

    void renderDepth(Scene &scene) override;
};