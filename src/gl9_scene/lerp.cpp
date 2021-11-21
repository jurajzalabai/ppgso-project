//
// Created by Tommy on 20. 11. 2021.
//

#include <glm/gtc/random.hpp>
#include "human.h"
#include "projectile.h"
#include "explosion.h"
#include "player.h"
#include "lerp.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources

Lerp::Lerp(glm::vec3 first, glm::vec3 second, float speed, float time, float backs_x, float backs_y, float backs_z) {
    // Set random scale speed and rotation
    firsts = first;
    seconds = second;
    flag = false;
    j = 0;
    speeds = speed;
    times = time;
    back_x = backs_x;
    back_y = backs_y;
    back_z = backs_z;

}

glm::vec3 bezierPoint(const glm::vec3 &p0, const glm::vec3 &p1, const float t) {
    glm::vec3 q0;
    q0 = p0 + t * (p1-p0);
    return {q0};
}

bool Lerp::update(Scene &scene, float dt) {
    age += dt;
    if (j < speeds and age > times){
        glm::vec3 q0;
        q0 = firsts + (static_cast<float>(j) / float(speeds)) * (seconds-firsts);
        scene.camera->position = q0;

        scene.camera->back.x = (back_x / j);
        scene.camera->back.y = (back_y / j);
        scene.camera->back.z = (back_z / j);

        j++;
        }


//    if (age > 5 && !flag){
//        for (int j = 0; j <= 100; j++) {
//            std::cout << "DSA" << std::endl;
//            glm::vec3 point;
//            point = bezierPoint(firsts, seconds, static_cast<float>(j) / float(100));
//            scene.camera->position = point;
//        }
//        flag = true;
//    }
    return true;
}

void Lerp::render(Scene &scene) {
}


void Lerp::bezierShape(Scene &scene, glm::vec3 first, glm::vec3 second, int count) {
    for (int j = 0; j <= count; j++) {
        glm::vec3 point;
        point = bezierPoint(first, second, static_cast<float>(j) / float(count));
        scene.camera->position = point;
        scene.camera->update();
    }
}




