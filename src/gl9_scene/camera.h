#pragma once
#include <memory>

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>
#include <src/gl9_scene/keyframe.h>

/*!
 * Simple camera object that keeps track of viewMatrix and projectionMatrix
 * the projectionMatrix is by default constructed as perspective projection
 * the viewMatrix is generated from up, position and back vectors on update
 */
class Camera {
private:
    unsigned long long int curr = 0;

public:
    glm::vec3 up{0,1,0};
    glm::vec3 position{0,15,100};
    glm::vec3 back{0,0,1};
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    float age{0.0f};
    bool autoMovement = true;
    int scene_num;
    std::vector<std::vector<Keyframe>> keyframes;

  /*!
   * Create new Camera that will generate viewMatrix and projectionMatrix based on its position, up and back vectors
   * @param fow - Field of view in degrees
   * @param ratio - Viewport screen ratio (usually width/height of the render window)
   * @param near - Distance to the near frustum plane
   * @param far - Distance to the far frustum plane
   */
  Camera(float fow, float ratio, float near, float far);

  /*!
   * Update Camera viewMatrix based on up, position and back vectors
   */
  void update(float dt);

  glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float age, float start, float duration);

protected:
};


