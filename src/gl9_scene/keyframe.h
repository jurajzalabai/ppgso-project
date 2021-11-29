#pragma once
#include <memory>
#include <ppgso/ppgso.h>

class Keyframe {
private:

public:

    glm::vec3 position;
    glm::vec3 rotation;
    float startTime;
    float duration;

    Keyframe(glm::vec3 position, glm::vec3 rotation, float startTime, float duration);

private:
};
