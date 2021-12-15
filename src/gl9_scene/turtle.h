#pragma once
#include <memory>

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"

class Turtle final : public Object {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Shader> shaderDepth;
    static std::unique_ptr<ppgso::Texture> texture;

    unsigned long long int curr = 0;

public:

    float age{0.0f};
    int scene_num = -1;
    std::vector<std::vector<Keyframe>> keyframes;

    Turtle();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene, unsigned int depthMap) override;

    void renderDepth(Scene &scene) override;

private:
};
