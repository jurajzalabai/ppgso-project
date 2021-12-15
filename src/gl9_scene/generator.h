#pragma once
#include "object.h"
#include "scene.h"

/*!
 * Example generator of objects
 * Constructs a new object during Update and adds it into the scene
 * Does not render anything
 */
class Generator final : public Object {
public:

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene, unsigned int depthMap) override;

    void renderDepth(Scene &scene) override;

    float time = 0.0f;
    float time_sand = 0.0f;
};
