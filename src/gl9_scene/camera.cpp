#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "camera.h"


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI/180.0f) * fow;

    keyframes = {Keyframe(glm::vec3(0,15,100), glm::vec3(0, 0, 1), 18.0f, 5.0f),
                 Keyframe(glm::vec3(50,20,30), glm::vec3(-0.6f, 0, 1), 0.0f, 0.0f)};
    curr = 0;
    position = keyframes[0].position;
    back = keyframes[0].rotation;

    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update(float dt) {
    age += dt;

    if (autoMovement && keyframes[curr].startTime < age) {
        if (keyframes[curr].duration != 0) {
            if (age < keyframes[curr].startTime + keyframes[curr].duration){
                position = lerp(keyframes[curr].position, keyframes[curr+1].position, age, keyframes[curr].startTime, keyframes[curr].duration);
                back = lerp(keyframes[curr].rotation, keyframes[curr+1].rotation, age, keyframes[curr].startTime, keyframes[curr].duration);
            }
            else {
                curr++;
            }
        }
    }
    std::cout<< " z camera: "<< position.z<< std::endl;
    std::cout<< " y camera: "<< position.y<< std::endl;
    std::cout<< " x camera: "<< position.x<< std::endl;
    std::cout<< " rotate camera: "<< back.z<< std::endl;
    std::cout<< " rotate camera: "<< back.y<< std::endl;
    std::cout<< " rotate camera: "<< back.x<< std::endl;
  viewMatrix = lookAt(position, position-back, up);
}

glm::vec3 Camera::cast(double u, double v) {
  // Create point in Screen coordinates
  glm::vec4 screenPosition{u,v,0.0f,1.0f};

  // Use inverse matrices to get the point in world coordinates
  auto invProjection = glm::inverse(projectionMatrix);
  auto invView = glm::inverse(viewMatrix);

  // Compute position on the camera plane
  auto planePosition = invView * invProjection * screenPosition;
  planePosition /= planePosition.w;

  // Create direction vector
  auto direction = glm::normalize(planePosition - glm::vec4{position,1.0f});
  return glm::vec3{direction};
}

glm::vec3 Camera::lerp(glm::vec3 a, glm::vec3 b, float age, float start, float duration){
    return a + ((age - start)/duration) * (b-a);
}
