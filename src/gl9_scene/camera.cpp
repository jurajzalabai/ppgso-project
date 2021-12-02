#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "camera.h"


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI/180.0f) * fow;

    keyframes = {
        {
        Keyframe(glm::vec3(25,30,30), glm::vec3(0, 0, 1), 0.0f, 6.0f),
        //let cajky
        Keyframe(glm::vec3(-35,18,45), glm::vec3(0, 0, 1), 6.0f, 1.5f),
        // smrt cajky
        Keyframe(glm::vec3(-35,5,45), glm::vec3(0, 0, 1), 12.0f, 3.0f),
        // zaber na ostrov
        Keyframe(glm::vec3(0,15,100), glm::vec3(0, 0, 1), 18.0f, 3.0f),
        // zaber na komin
        Keyframe(glm::vec3(50,20,30), glm::vec3(-0.6f, 0, 1), 28.0f, 4.0f),
        // korytnacka
        Keyframe(glm::vec3(1.0f,14.0f, 12.0f), glm::vec3(0.314159f,0.418879f,1), 40.0f, 3.0f),
        // kokos
        Keyframe(glm::vec3(-17.0f,19.0f, 36.0f), glm::vec3(0.314159f,0.418879f,1), 48.0f, 4.0f),
        // prejdeme do dveri
        Keyframe(glm::vec3(21,8,3), glm::vec3(-7.95f,3.63f,3.63f), 0.0f, 0.0f)},

        {
        Keyframe(glm::vec3(1, 9, 96), glm::vec3(0.05f, 0.1f, 1), 65.0f, 4.0f),
        // prichod ku stolu
        Keyframe(glm::vec3(12, 9, 71), glm::vec3(0.25f, 0.57f, 1), 73.0f, 2.0f),
        // pred stol
        Keyframe(glm::vec3(2, 9, 63), glm::vec3(-8.0f, 5.7f, 1), 75.0f, 4.0f),
        // prechod ponad stolom
        Keyframe(glm::vec3(4, 9, 53), glm::vec3(-7.0f, 5.7f, -7.1f), 0.0f, 0.0f)},

        {Keyframe(glm::vec3(0,15,100), glm::vec3(0, 0, 1), 0.0f, 0.0f)}
    };

    curr = 0;

    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update(float dt) {
    age += dt;

    if (autoMovement && keyframes[scene_num][curr].startTime < age) {
        if (keyframes[scene_num][curr].duration != 0) {
            if (age < keyframes[scene_num][curr].startTime + keyframes[scene_num][curr].duration){
                position = lerp(keyframes[scene_num][curr].position, keyframes[scene_num][curr+1].position, age, keyframes[scene_num][curr].startTime, keyframes[scene_num][curr].duration);
                back = lerp(keyframes[scene_num][curr].rotation, keyframes[scene_num][curr+1].rotation, age, keyframes[scene_num][curr].startTime, keyframes[scene_num][curr].duration);
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
    std::cout<< " age: "<< age << std::endl;
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
