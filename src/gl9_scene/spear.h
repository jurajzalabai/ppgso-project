#pragma once
#include <memory>

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"
#include "keyframe.h"

/*!
 * Simple asteroid object
 * This sphere object represents an instance of mesh geometry
 * It initializes and loads all resources only once
 * It will move down along the Y axis and self delete when reaching below -10
 */
class Spear final : public Object {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    unsigned long long int curr = 0;

    // Speed and rotational momentum
    glm::vec3 speed;

public:

    // Age of the object in seconds
    float age{0.0f};
    float fall_time;
    int scene_num = -1;
    std::vector<std::vector<Keyframe>> keyframes;

    /*!
     * Create new asteroid
     */
    Spear();

    /*!
     * Update asteroid
     * @param scene Scene to interact with
     * @param dt Time delta for animation purposes
     * @return
     */
    bool update(Scene &scene, float dt) override;

    /*!
     * Render asteroid
     * @param scene Scene to render in
     */
    void render(Scene &scene, unsigned int depthMap) override;

    void renderDepth(Scene &scene) override;


private:
};

