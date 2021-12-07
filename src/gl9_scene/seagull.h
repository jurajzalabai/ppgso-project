#pragma once
#include <ppgso/ppgso.h>

#include "object.h"
#include "keyframe.h"

/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
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
    glm::vec3 flight;
    glm::vec3 wind;
    glm::vec3 lift;
    std::vector<std::vector<Keyframe>> keyframes;

    /*!
     * Create a new player
     */
    Seagull();

    /*!
     * Update player position considering keyboard inputs
     * @param scene Scene to update
     * @param dt Time delta
     * @return true to delete the object
     */
    bool update(Scene &scene, float dt) override;

    /*!
     * Render player
     * @param scene Scene to render in
     */
    void render(Scene &scene) override;
};