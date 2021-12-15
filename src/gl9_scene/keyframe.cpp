#include "keyframe.h"

Keyframe::Keyframe(glm::vec3 position, glm::vec3 rotation, float startTime, float duration) {
    this->position = position;
    this->rotation = rotation;
    this->startTime = startTime;
    this->duration = duration;
}