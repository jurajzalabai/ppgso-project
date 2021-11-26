#include <glm/gtc/random.hpp>
#include "keyframe.h"

//Keyframe::Keyframe(glm::vec3 position, glm::vec3 rotation, float arrivalTime, float departureTime) {
//    this->position = position;
//    this->rotation = rotation;
//    this->arrivalTime = arrivalTime;
//    this->departureTime = departureTime;
//}

//Keyframe::Keyframe(glm::vec3 position, glm::vec3 rotation, float duration) {
//    this->position = position;
//    this->rotation = rotation;
//    this->duration = duration;
//}

Keyframe::Keyframe(glm::vec3 position, glm::vec3 rotation, float startTime, float duration) {
    this->position = position;
    this->rotation = rotation;
    this->startTime = startTime;
    this->duration = duration;
}