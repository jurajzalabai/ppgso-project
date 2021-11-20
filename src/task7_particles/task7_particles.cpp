// Task 7 - Dynamically generate objects in a 3D scene
//        - Implement a particle system where particles have position and speed
//        - Any object can be a generator and can add objects to the scene
//        - Create dynamic effect such as fireworks, rain etc.
//        - Encapsulate camera in a class

#include <iostream>
#include <vector>
#include <map>
#include <list>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include <ppgso/ppgso.h>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

const unsigned int SIZE = 512;

class Camera {
public:
    // TODO: Add parameters
    glm::vec3 eye = {0, 0, -10};
    glm::vec3 center = {0, 0, 0};
    glm::vec3 up = {0, 1, 0};
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    /// Representaiton of
    /// \param fov - Field of view (in degrees)
    /// \param ratio - Viewport ratio (width/height)
    /// \param near - Distance of the near clipping plane
    /// \param far - Distance of the far clipping plane
    Camera(float fov = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 10.0f) {
        // TODO: Initialize perspective projection (hint: glm::perspective)
        projectionMatrix = glm::perspective(fov, ratio, near, far);
    }

    /// Recalculate viewMatrix from position, rotation and scale
    void update() {
        // TODO: Update viewMatrix (hint: glm::lookAt)
        viewMatrix = glm::lookAt(eye, center, up);
    }
};

/// Abstract renderable object interface
class Renderable; // Forward declaration for Scene
using Scene = std::list<std::unique_ptr<Renderable>>; // Type alias

class Renderable {
public:
    // Virtual destructor is needed for abstract interfaces
    virtual ~Renderable() = default;

    /// Render the object
    /// \param camera - Camera to use for rendering
    virtual void render(const Camera& camera) = 0;

    /// Update the object. Useful for specifing animation and behaviour.
    /// \param dTime - Time delta
    /// \param scene - Scene reference
    /// \return - Return true to keep object in scene
    virtual bool update(float dTime, Scene &scene, bool sick) = 0;
};

/// Basic particle that will render a sphere
/// TODO: Implement Renderable particle
class Sickness final : public Renderable {
    // Static resources shared between all particles
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;

    // TODO: add more parameters as needed
public:

    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 color;
    glm::mat4 modelMatrix = glm::mat4 {1.0f};
    glm::vec3 scale;
    float age = 0;
    /// Construct a new Particle
    /// \param p - Initial position
    /// \param s - Initial speed
    /// \param c - Color of particle
    Sickness(glm::vec3 p, glm::vec3 s, glm::vec3 c, glm::vec3 sc) {
        // First particle will initialize resources
        position = p;
        speed = s;
        color = c;
        scale = sc;
        age = 0;
        if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
        if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
    }

    bool update(float dTime, Scene &scene, bool sick) override {
        // TODO: Animate position using speed and dTime.
        // - Return true to keep the object alive
        // - Returning false removes the object from the scene
        // - hint: you can add more particles to the scene here also
        position += speed * dTime;
        age += dTime;
        modelMatrix = glm::translate( glm::mat4 {1.0f}, position);
        modelMatrix *= glm::scale(glm::mat4 {1.0f}, scale);
        if (age > 1.0f) {
            return false;
        }
        return true;
    }

    void render(const Camera& camera) override {
        // TODO: Render the object
        // - Use the shader
        // - Setup all needed shader inputs
        // - hint: use OverallColor in the color_vert_glsl shader for color
        // - Render the mesh
        shader->use();

        shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
        shader->setUniform("ViewMatrix", camera.viewMatrix);

        shader->setUniform("ModelMatrix", modelMatrix);
        shader->setUniform("OverallColor", color);

        mesh->render();
    }
};

class Particle final : public Renderable {
    // Static resources shared between all particles
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;

    // TODO: add more parameters as needed
public:

    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 color;
    glm::mat4 modelMatrix = glm::mat4 {1.0f};
    glm::vec3 scale;
    float age = 0;
    /// Construct a new Particle
    /// \param p - Initial position
    /// \param s - Initial speed
    /// \param c - Color of particle
    Particle(glm::vec3 p, glm::vec3 s, glm::vec3 c, glm::vec3 sc) {
        // First particle will initialize resources
        position = p;
        speed = s;
        color = c;
        scale = sc;
        age = 0;
        if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
        if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
    }

    bool update(float dTime, Scene &scene, bool sick) override {
        // TODO: Animate position using speed and dTime.
        // - Return true to keep the object alive
        // - Returning false removes the object from the scene
        // - hint: you can add more particles to the scene here also
        position += speed * dTime;
        age += dTime;
        modelMatrix = glm::translate( glm::mat4 {1.0f}, position);
        modelMatrix *= glm::scale(glm::mat4 {1.0f}, scale);
        glm::vec3 color2 = {0, 1, 0};
        glm::vec3 scale2 = {.05, .05, .05};
        if (sick) {
            float vx = glm::linearRand(-2.0f, 2.0f);
            float vy = glm::linearRand(-2.0f, 2.0f);
            glm::vec3 speed2 = {vx, vy, 0};
            auto particle = new Sickness(position, speed2 + speed*1.5f, color2, scale2);
            scene.push_back(std::unique_ptr<Sickness>(particle));
        }
        if (age > 5.0f) {
            return false;
        }
        return true;
    }

    void render(const Camera& camera) override {
        // TODO: Render the object
        // - Use the shader
        // - Setup all needed shader inputs
        // - hint: use OverallColor in the color_vert_glsl shader for color
        // - Render the mesh
        shader->use();

        shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
        shader->setUniform("ViewMatrix", camera.viewMatrix);

        shader->setUniform("ModelMatrix", modelMatrix);
        shader->setUniform("OverallColor", color);

        mesh->render();
    }
};

// Static resources need to be instantiated outside of the class as they are globals
std::unique_ptr<ppgso::Mesh> Particle::mesh;
std::unique_ptr<ppgso::Shader> Particle::shader;

std::unique_ptr<ppgso::Mesh> Sickness::mesh;
std::unique_ptr<ppgso::Shader> Sickness::shader;

class ParticleWindow : public ppgso::Window {
private:
    // Scene of objects
    Scene scene;

    // Create camera
    Camera camera = {120.0f, (float)width/(float)height, 1.0f, 400.0f};

    // Store keyboard state
    std::map<int, int> keys;
public:
    ParticleWindow() : Window{"task7_particles", SIZE, SIZE} {
        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }

    void onKey(int key, int scanCode, int action, int mods) override {
        // Collect key state in a map
        keys[key] = action;
        glm::vec3 position = {0, 0, 0};
        float vx = glm::linearRand(-1.0f, 1.0f);
        float vy = glm::linearRand(-1.0f, 1.0f);
        glm::vec3 speed = {vx, vy, 0};
        glm::vec3 color = {0, 1, 1};
        glm::vec3 scale = {1, 1, 1};
        if (keys[GLFW_KEY_SPACE]) {
            // TODO: Add renderable object to the scene
            auto p = std::make_unique<Particle>(position, speed, color, scale);
            scene.push_back(std::move(p));
        }
    }

    void onIdle() override {
        // Track time
        static auto time = (float) glfwGetTime();
        // Compute time delta
        float dTime = (float)glfwGetTime() - time;
        time = (float) glfwGetTime();

        // Set gray background
        glClearColor(.1f,.1f,.1f,1.0f);

        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update all objects in scene
        // Because we need to delete while iterating this is implemented using c++ iterators
        // In most languages mutating the container during iteration is undefined behaviour
        auto i = std::begin(scene);
        while (i != std::end(scene)) {
            // Update object and remove from list if needed
            auto obj = i->get();
            if (!obj->update(dTime, scene, keys[GLFW_KEY_C]))
                i = scene.erase(i);
            else
                ++i;
        }

        camera.update();
        // Render every object in scene
        for(auto& object : scene) {
            object->render(camera);
        }
    }
};

int main() {
    // Create new window
    auto window = ParticleWindow{};

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}
