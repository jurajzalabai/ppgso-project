#pragma once
#include <memory>

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"

class Walls final : public Object {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:

    Walls();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene, unsigned int depthMap) override;

    void renderDepth(Scene &scene) override;

private:
};
