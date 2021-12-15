#pragma once
#include <memory>
#include <list>
#include <map>

#include <glm/glm.hpp>

// Forward declare a scene
class Scene;

class Object {
public:
  // Define default constructors as this is an abstract class
  Object() = default;
  Object(const Object&) = default;
  Object(Object&&) = default;
  virtual ~Object() {};

  virtual bool update(Scene &scene, float dt) = 0;

  virtual void render(Scene &scene, unsigned int depthMap) = 0;

  virtual void renderDepth(Scene &scene) = 0;

  // Object properties
  glm::vec3 position{0,0,0};
  glm::vec3 rotation{0,0,0};
  glm::vec3 scale{1,1,1};
  glm::mat4 modelMatrix{1};
  glm::mat4 modelMatrixNotScaled{1};

  Object *parent = nullptr;
  Object *child = nullptr;

protected:

  void generateModelMatrix();

  glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float age, float start, float duration);

  glm::vec3 quadratic_lerp(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, float age, float start, float duration);
};

