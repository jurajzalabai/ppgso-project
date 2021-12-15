#pragma once
#include <memory>

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"

class House final : public Object {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    float age{0.0f};

    House();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene, unsigned int depthMap) override;

    void renderDepth(Scene &scene) override;

private:
};
