// Example gl_scene
// - Introduces the concept of a dynamic scene of objects
// - Uses abstract object interface for Update and Render steps
// - Creates a simple game scene with Player, Asteroid and Space objects
// - Contains a generator object that does not render but adds Asteroids to the scene
// - Some objects use shared resources and all object deallocations are handled automatically
// - Controls: LEFT, RIGHT, "R" to reset, SPACE to fire

#include <iostream>
#include <map>
#include <list>

#include <ppgso/ppgso.h>

#include "camera.h"
#include "scene.h"
#include "seagull.h"
#include "spear.h"
#include "island.h"
#include "palmTree.h"
#include "coconut.h"
#include "turtle.h"
#include "ocean.h"
#include "human.h"
#include "house.h"
#include "lerp.h"
#include "chimney.h"
#include "generator.h"
#include "fireplace.h"
#include "table.h"
#include "plate.h"
#include "mug.h"
#include "lamp.h"
#include "ceilinglamp.h"

const unsigned int SIZE = 800;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public ppgso::Window {
private:
  Scene scene;
  bool animate = true;

  /*!
   * Reset and initialize the game scene
   * Creating unique smart pointers to objects that are stored in the scene object list
   */
    void initScene() {
        scene.objects.clear();

    // Add space background
    //scene.objects.push_back(std::make_unique<Space>());

//     Add generator to scene
//    auto generator = std::make_unique<Generator>();
//    generator->position.y = 10.0f;
//    scene.objects.push_back(move(generator));

        // Add player to the scene
        auto spear = std::make_unique<Spear>();
        spear->position = glm::vec3(-1,5,47);
        scene.objects.push_back(move(spear));

        auto seagull = std::make_unique<Seagull>();
        seagull->position = glm::vec3(25,30,0);
        scene.objects.push_back(move(seagull));

        auto palmTree = std::make_unique<PalmTree>();
        palmTree->position = glm::vec3(-35,0,12);
        scene.objects.push_back(move(palmTree));

        auto coconut = std::make_unique<Coconut>();
        coconut->position = glm::vec3(-22,19,6);
        scene.objects.push_back(move(coconut));

        auto generator = std::make_unique<Generator>();
        scene.objects.push_back(move(generator));

        auto turtle = std::make_unique<Turtle>();
        turtle->position = glm::vec3(-15,1,-30);
        scene.objects.push_back(move(turtle));

        auto human = std::make_unique<Human>();
        //        human->position = glm::vec3(-1,-1,50);
        scene.objects.push_back(move(human));

        auto house = std::make_unique<House>();
        house->position = glm::vec3(50,0,0);
        house->scale *= 1.6;
        scene.objects.push_back(move(house));

        auto chimney = std::make_unique<Chimney>();
        chimney->position = glm::vec3(62,15,10);
        scene.objects.push_back(move(chimney));

        auto table = std::make_unique<Table>();
        table->position = glm::vec3(0,0,25);
        table->rotation.z = (ppgso::PI/180)*(-90);
        scene.objects.push_back(move(table));

        auto plate = std::make_unique<Plate>();
        plate->position = glm::vec3(0,2.5f,25);
        scene.objects.push_back(move(plate));

        auto lamp = std::make_unique<Lamp>();
        lamp->position = glm::vec3(2,2.5f,25);
        scene.objects.push_back(move(lamp));

        auto mug = std::make_unique<Mug>();
        mug->position = glm::vec3(4,2.5f,25);
        scene.objects.push_back(move(mug));

        auto ceilinglamp = std::make_unique<CeilingLamp>();
        ceilinglamp->position = glm::vec3(4, 5, 25);
        scene.objects.push_back(move(ceilinglamp));

        auto fireplace = std::make_unique<Fireplace>();
        fireplace->position = glm::vec3(-10,0,25);
        fireplace->rotation.x = (ppgso::PI/180)*(-90);
        scene.objects.push_back(move(fireplace));

        // Add player to the scene
        auto island = std::make_unique<Island>();
        island->position = glm::vec3(0,0,0);
        island->rotation.z = (ppgso::PI/180)*(-90);
        scene.objects.push_back(move(island));

        auto ocean = std::make_unique<Ocean>();
        ocean->position = glm::vec3(0,10,0);
        ocean->scale.x *= 10;
        ocean->scale.z *= 10;
        scene.objects.push_back(move(ocean));

//        auto lerp = std::make_unique<Lerp>(glm::vec3(0,15,100), glm::vec3(0,15,30), 500, 4, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//        scene.objects.push_back(move(lerp));
//
//        auto lerp2 = std::make_unique<Lerp>(glm::vec3(0,15,30), glm::vec3(75,30,30), 500, 8, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.5f, 0.5f));
//        scene.objects.push_back(move(lerp2));
//
//        auto lerp3 = std::make_unique<Lerp>(glm::vec3(75,30,30), glm::vec3(70,30,-60), 1000, 11, glm::vec3(0.0f, 0.5f, 0.5f), glm::vec3(1.2, 0, -1.31));
//        scene.objects.push_back(move(lerp3));


        // Create a camera
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 200.0f);
        scene.camera = move(camera);

  }


public:
  /*!
   * Construct custom game window
   */
  SceneWindow() : Window{"gl9_scene", SIZE, SIZE} {
    //hideCursor();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    // Initialize OpenGL state
    // Enable Z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable polygon culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    initScene();
  }

  /*!
   * Handles pressed key when the window is focused
   * @param key Key code of the key being pressed/released
   * @param scanCode Scan code of the key being pressed/released
   * @param action Action indicating the key state change
   * @param mods Additional modifiers to consider
   */
  void onKey(int key, int scanCode, int action, int mods) override {
    scene.keyboard[key] = action;

      if (key == GLFW_KEY_W ) {
          scene.camera->position.y += 1;
      }

      if (key == GLFW_KEY_S) {
          scene.camera->position.y -= 1;
      }

      if (key == GLFW_KEY_D) {
          scene.camera->position.x += 1;
      }

      if (key == GLFW_KEY_A) {
          scene.camera->position.x -= 1;
      }

      if (key == GLFW_KEY_E) {
          scene.camera->position.z -= 1;
      }

      if (key == GLFW_KEY_Q) {
          scene.camera->position.z += 1;
      }

      if (key == GLFW_KEY_X) {
          scene.camera->back.x += (ppgso::PI/180)*(-3);
      }

      if (key == GLFW_KEY_Z) {
          scene.camera->back.x -= (ppgso::PI/180)*(-3);
      }

      if (key == GLFW_KEY_C) {
          scene.camera->back.y += (ppgso::PI/180)*(-3);
      }

      if (key == GLFW_KEY_V) {
          scene.camera->back.y -= (ppgso::PI/180)*(-3);
      }

      if (key == GLFW_KEY_B) {
          scene.camera->back.z += (ppgso::PI/180)*(-3);
      }

      if (key == GLFW_KEY_N) {
          scene.camera->back.z -= (ppgso::PI/180)*(-3);
      }

      if (key == GLFW_KEY_T) {
          scene.camera->autoMovement = false;
      }

      if (key == GLFW_KEY_1) {
          scene.camera->position.z = 75.0f;
          scene.camera->position.x = 0.0f;
          scene.camera->position.y = 10.0f;
          scene.camera->back.z = 1.0f;
          scene.camera->back.y = 0;
          scene.camera->back.x = 0;
      }

      if (key == GLFW_KEY_2) {
          scene.camera->position.z = 36.0f;
          scene.camera->position.x = 53.0f;
          scene.camera->position.y = 20.0f;
          scene.camera->back.z = 1.20944f;
          scene.camera->back.y = 0;
          scene.camera->back.x = -0.418879f;
      }

      if (key == GLFW_KEY_3) {
          scene.camera->position.z = 12.0f;
          scene.camera->position.x = 1.0f;
          scene.camera->position.y = 14.0f;
          scene.camera->back.z = 1.0f;
          scene.camera->back.y = 0.418879f;
          scene.camera->back.x = 0.314159f;
      }

      if (key == GLFW_KEY_4) {
          scene.camera->position.z = 36.0f;
          scene.camera->position.x = -17.0f;
          scene.camera->position.y = 19.0f;
          scene.camera->back.z = 1.0f;
          scene.camera->back.y = 0.418879f;
          scene.camera->back.x = 0.314159f;
      }

      if (key == GLFW_KEY_5) {
          scene.camera->position.z = 4.0f;
          scene.camera->position.x = 23.0f;
          scene.camera->position.y = 7.0f;
          scene.camera->back.z = 1.0f;
          scene.camera->back.y = 0.0f;
          scene.camera->back.x = -3.97935f;
      }

      if (key == GLFW_KEY_6) {
          scene.camera->position.z = 12.0f;
          scene.camera->position.x = 45.0f;
          scene.camera->position.y = 11.0f;
          scene.camera->back.z = 1.0f;
          scene.camera->back.y = 0.733038f;
          scene.camera->back.x = 0.047752f;
      }

      if (key == GLFW_KEY_7) {
          scene.camera->position.z = 7.0f;
          scene.camera->position.x = 23.0f;
          scene.camera->position.y = 7.0f;
          scene.camera->back.z = 0.0f;
          scene.camera->back.y = 0.0f;
          scene.camera->back.x = -1.0f;
      }

      if (key == GLFW_KEY_8) {
          scene.camera->position.z = 7.0f;
          scene.camera->position.x = 23.0f;
          scene.camera->position.y = 7.0f;
          scene.camera->back.z = 0.0f;
          scene.camera->back.y = 0.0f;
          scene.camera->back.x = -1.0f;
      }


    // Reset
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
      initScene();
    }

    // Pause
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
      animate = !animate;
    }
  }

  /*!
   * Handle cursor position changes
   * @param cursorX Mouse horizontal position in window coordinates
   * @param cursorY Mouse vertical position in window coordinates
   */
  void onCursorPos(double cursorX, double cursorY) override {
    scene.cursor.x = cursorX;
    scene.cursor.y = cursorY;
  }

  /*!
   * Handle cursor buttons
   * @param button Mouse button being manipulated
   * @param action Mouse bu
   * @param mods
   */
  void onMouseButton(int button, int action, int mods) override {
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
      scene.cursor.left = action == GLFW_PRESS;

      if (scene.cursor.left) {
        // Convert pixel coordinates to Screen coordinates
        double u = (scene.cursor.x / width - 0.5f) * 2.0f;
        double v = - (scene.cursor.y / height - 0.5f) * 2.0f;

        // Get mouse pick vector in world coordinates
        auto direction = scene.camera->cast(u, v);
        auto position = scene.camera->position;

        // Get all objects in scene intersected by ray
        auto picked = scene.intersect(position, direction);

        // Go through all objects that have been picked
        for (auto &obj: picked) {
          // Pass on the click event
          obj->onClick(scene);
        }
      }
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT) {
      scene.cursor.right = action == GLFW_PRESS;
    }
  }

  /*!
   * Window update implementation that will be called automatically from pollEvents
   */
  void onIdle() override {
    // Track time
    static auto time = (float) glfwGetTime();

    // Compute time delta
    float dt = animate ? (float) glfwGetTime() - time : 0;

    time = (float) glfwGetTime();

    // Set gray background
    glClearColor(.5f, .5f, .5f, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update and render all objects
    scene.update(dt);
    scene.render();
  }
};

int main() {
  // Initialize our window
  SceneWindow window;

  // Main execution loop
  while (window.pollEvents()) {}

  return EXIT_SUCCESS;
}
