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
#include "floor.h"
#include "walls.h"
#include "mug.h"
#include "lamp.h"
#include "ceilinglamp.h"
#include "sphere.h"

const unsigned int SIZE = 800;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public ppgso::Window {
private:
  bool animate = true;

public:
  /*!
   * Construct custom game window
   */
  Scene scene;

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

  }

    void initScene() {
        scene.objects.clear();
        scene.scene_num++;
        // Add space background
        //scene.objects.push_back(std::make_unique<Space>());

//     Add generator to scene
//    auto generator = std::make_unique<Generator>();
//    generator->position.y = 10.0f;
//    scene.objects.push_back(move(generator));

        if (scene.scene_num == 0) {
            auto spear = std::make_unique<Spear>();
            spear->age = scene.age;
            spear->scene_num = scene.scene_num;
            spear->position = spear->keyframes[spear->scene_num][0].position;
            spear->rotation = spear->keyframes[spear->scene_num][0].rotation;
            scene.objects.push_back(move(spear));

            auto seagull = std::make_unique<Seagull>();
            seagull->age = scene.age;
            seagull->scene_num = scene.scene_num;
            seagull->position = seagull->keyframes[seagull->scene_num][0].position;
            seagull->rotation = seagull->keyframes[seagull->scene_num][0].rotation;
            scene.objects.push_back(move(seagull));

            auto human = std::make_unique<Human>();
            human->age = scene.age;
            human->scene_num = scene.scene_num;
            human->position = human->keyframes[human->scene_num][0].position;
            human->rotation = human->keyframes[human->scene_num][0].rotation;
            scene.objects.push_back(move(human));
        }

        auto palmTree = std::make_unique<PalmTree>();
        palmTree->age = scene.age;
        palmTree->position = glm::vec3(-35,0,12);
        scene.objects.push_back(move(palmTree));

        auto coconut = std::make_unique<Coconut>();
        coconut->age = scene.age;
        coconut->position = glm::vec3(-22,19,6);
        scene.objects.push_back(move(coconut));

        auto generator = std::make_unique<Generator>();
        generator->time = scene.age;
        scene.objects.push_back(move(generator));

        auto turtle = std::make_unique<Turtle>();
        turtle->age = scene.age;
        turtle->scene_num = scene.scene_num;
        turtle->position = turtle->keyframes[turtle->scene_num][0].position;
        turtle->rotation = turtle->keyframes[turtle->scene_num][0].rotation;
        scene.objects.push_back(move(turtle));

        auto house = std::make_unique<House>();
        house->position = glm::vec3(50,0,0);
        house->scale *= 1.6;
        scene.objects.push_back(move(house));

        auto chimney = std::make_unique<Chimney>();
        chimney->position = glm::vec3(62,15,10);
        scene.objects.push_back(move(chimney));

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
        camera->age = scene.age;
        camera->scene_num = scene.scene_num;
        camera->position = camera->keyframes[camera->scene_num][0].position;
        camera->back = camera->keyframes[camera->scene_num][0].rotation;
        scene.camera = move(camera);

    }

    void initInteriorScene() {
        scene.objects.clear();
        scene.scene_num++;
        //TODO: zmenit svetla, tak aby vyzerali ze svietia
        //TODO: pohyb v druhej scene
        //TODO: kamery v druhej scene
        //TODO: prepinanie medzi scenami

        //TODO: tiene
        //TODO: zapad slnka
        //TODO: textura podlahy, mozno steny
        //TODO: ohen textura
        //TODO: refaktor kodu
        //TODO: let vtaka camera - parent
        //TODO: keyframe - na vsetko
        //TODO: spravne textury na vsetko


        //TODO: otazky - ked sa dlho nacitava scena
        //TODO: ked nechcem vidiet smoke zo vsade
        //TODO: textury ci na vsetkom, nevieme najst
        //TODO: ci vsetko cez keyframes.. pady
        //TODO: ako to maju ostatni ? zatial staci ? co dodat ?
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 200.0f);
        camera->age = scene.age;
        camera->scene_num = scene.scene_num;
        camera->position = camera->keyframes[camera->scene_num][0].position;
        camera->back = camera->keyframes[camera->scene_num][0].rotation;
        scene.camera = move(camera);

        auto generator = std::make_unique<Generator>();
        generator->time = scene.age;
        scene.objects.push_back(move(generator));

        auto floor = std::make_unique<Floor>();
        floor->position = glm::vec3(0, 0, 60);
        scene.objects.push_back(move(floor));

        auto bulb = std::make_unique<Sphere>();
        bulb->position = glm::vec3(8.14, 5.4, 62);
        bulb->scale *= 0.3;
        bulb->color = glm::vec3(1.0f);
        scene.objects.push_back(move(bulb));

        auto bulb_ceiling = std::make_unique<Sphere>();
        bulb_ceiling->position = glm::vec3(0, 17, 63);
        bulb_ceiling->scale *= 3;
        bulb_ceiling->color = glm::vec3(1.0f);
        scene.objects.push_back(move(bulb_ceiling));

        auto table = std::make_unique<Table>();
        table->position = glm::vec3(9, 1, 60);
        scene.objects.push_back(move(table));

        auto plate = std::make_unique<Plate>();
        plate->position = glm::vec3(9, 3.2, 60);
        scene.objects.push_back(move(plate));

        auto walls = std::make_unique<Walls>();
        walls->position = glm::vec3(0,0,60);
        scene.objects.push_back(move(walls));

        auto fireplace = std::make_unique<Fireplace>();
        fireplace->position = glm::vec3(0, 0, 33);
        fireplace->rotation.x = (ppgso::PI / 180) * (-90);
        scene.objects.push_back(move(fireplace));

        auto lamp = std::make_unique<Lamp>();
        lamp->position = glm::vec3(9, 3.2, 62);
        lamp->scale *= 0.5;
        lamp->rotation.z = (ppgso::PI / 180) * (-90);
        scene.objects.push_back(move(lamp));

        auto mug = std::make_unique<Mug>();
        mug->position = glm::vec3(9, 3.2, 58);
        mug->scale *= 0.5;
        scene.objects.push_back(move(mug));

        auto ceilinglamp = std::make_unique<CeilingLamp>();
        ceilinglamp->position = glm::vec3(0, 16.10, 63);
        scene.objects.push_back(move(ceilinglamp));

        auto human = std::make_unique<Human>();
        human->age = scene.age;
        human->scene_num = scene.scene_num;
        human->position = human->keyframes[human->scene_num][0].position;
        human->rotation = human->keyframes[human->scene_num][0].rotation;
        scene.objects.push_back(move(human));

        auto spear = std::make_unique<Spear>();
        spear->age = scene.age;
        spear->scene_num = scene.scene_num;
        spear->position = spear->keyframes[spear->scene_num][0].position;
        spear->rotation = spear->keyframes[spear->scene_num][0].rotation;
        scene.objects.push_back(move(spear));

        auto seagull = std::make_unique<Seagull>();
        seagull->age = scene.age;
        seagull->scene_num = scene.scene_num;
        seagull->position = seagull->keyframes[seagull->scene_num][0].position;
        seagull->rotation = seagull->keyframes[seagull->scene_num][0].rotation;
        scene.objects.push_back(move(seagull));
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
    window.initScene();
    // Main execution loop
    while (window.pollEvents()) {
        if (window.scene.age >= 52.0f && window.scene.scene_num == 0){
            window.initInteriorScene();
        }
        if (window.scene.age >= 80.0f && window.scene.scene_num == 1){
            window.initScene();
        }
    }

    return EXIT_SUCCESS;
}
