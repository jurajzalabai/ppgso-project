#pragma once
#include <memory>

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"

/*!
 * Simple asteroid object
 * This sphere object represents an instance of mesh geometry
 * It initializes and loads all resources only once
 * It will move down along the Y axis and self delete when reaching below -10
 */
class Lerp final : public Object {
private:
    // Static resources (Shared between instances)

    // Age of the object in seconds
    float age{0.0f};
    glm::vec3 firsts;
    glm::vec3 seconds;
    bool flag;
    float j;
    float speeds;
    float times;
    float back_x;
    float back_y;
    float back_z;

    /*!
     * Split the asteroid into multiple pieces and spawn an explosion object.
     *
     * @param scene - Scene to place pieces and explosion into
     * @param explosionPosition - Initial position of the explosion
     * @param explosionScale - Scale of the explosion
     * @param pieces - Asteroid pieces to generate
     */

public:
    /*!
     * Create new asteroid
     */
    Lerp(glm::vec3 first, glm::vec3 second, float speed, float time, float backs_x, float backs_y, float backs_z);

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

    /*!
     * Custom click event for asteroid
     */
    void render(Scene &scene) override;


    void bezierShape(Scene &scene, glm::vec3 first, glm::vec3 second, int count);

private:
};