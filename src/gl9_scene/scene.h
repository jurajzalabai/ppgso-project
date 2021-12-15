#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>

#include "object.h"
#include "camera.h"


class Scene {
  public:

    void update(float time);

    void render(unsigned int depthMap);

    void renderDepth();

    // Camera object
    std::unique_ptr<Camera> camera;

    // All objects to be rendered in scene
    std::list< std::unique_ptr<Object> > objects;

    // Keyboard state
    std::map< int, int > keyboard;

    // Lights, in this case using only simple directional diffuse lighting
    glm::vec3 lightDirection{1.0f, 1.0f, 1.0f};

    float age={0.0};

    int scene_num=-1;
    glm::vec3 palmTree_position;
    glm::vec3 coconut_position = glm::vec3{0, 0, 0};
    glm::vec3 coconut_rotation;
    float fallenCoconut;

};

#endif // _PPGSO_SCENE_H
