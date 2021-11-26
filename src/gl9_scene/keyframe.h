#pragma once
#include <memory>

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"

class Keyframe {
private:

public:

    glm::vec3 position;
    glm::vec3 rotation;
//    float arrivalTime;
//    float departureTime;
    float startTime;
    float duration;

//    Keyframe(glm::vec3 position, glm::vec3 rotation, float arrivalTime, float departureTime);
//    Keyframe(glm::vec3 position, glm::vec3 rotation, float duration);
    Keyframe(glm::vec3 position, glm::vec3 rotation, float startTime, float duration);

private:
};
