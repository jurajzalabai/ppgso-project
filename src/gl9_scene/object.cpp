#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

#include "object.h"

void Object::generateModelMatrix() {
    if (parent != nullptr) {
        modelMatrixNotScaled = parent->modelMatrixNotScaled *
                               glm::translate(glm::mat4(1.0f), position)
                               * glm::orientate4(rotation);
    }
    else {
        modelMatrixNotScaled =
                glm::translate(glm::mat4(1.0f), position)
                * glm::orientate4(rotation);
    }
    modelMatrix = modelMatrixNotScaled * glm::scale(glm::mat4(1.0f), scale);
}

glm::vec3 Object::lerp(glm::vec3 a, glm::vec3 b, float age, float start, float duration){
    return a + ((age - start)/duration) * (b-a);
}

glm::vec3 Object::quadratic_lerp(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, float age, float start, float duration) {
    glm::vec3 r0, r1;
    r0 = a + ((age - start)/duration) * (b-a);
    r1 = b + ((age - start)/duration) * (c-b);
    glm::vec3 s;
    s = r0 + ((age - start)/duration) * (r1-r0);
    return {s};
}

glm::vec3 Object::gravity(float mass) {
    return glm::vec3(0, -(mass * 9.81f), 0);
}