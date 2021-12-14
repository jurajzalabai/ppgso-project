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
#include "sky.h"
#include "palmLeaves.h"
#include "fire.h"
#include "boots.h"
#include "eyes.h"
#include "pants.h"
#include "shirt.h"
#include <shaders/blur_frag_glsl.h>
#include <shaders/blur_vert_glsl.h>
#include <shaders/bloom_vert_glsl.h>
#include <shaders/bloom_frag_glsl.h>

const unsigned int SIZE = 800;
const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
/*!
 * Custom windows for our simple game
 */
class SceneWindow : public ppgso::Window {
private:
  bool animate = true;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Shader> shader_bloom;
    unsigned int rboDepth;
    unsigned int colorBuffers[2];
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];
    unsigned int hdrFBO;
    //shadows
    unsigned int depthMapFBO;
    unsigned int depthMap;

public:
  /*!
   * Construct custom game window
   */
  Scene scene;

  SceneWindow() : Window{"gl9_scene", SIZE, SIZE} {
    //hideCursor();
      if (!shader) shader = std::make_unique<ppgso::Shader>(blur_vert_glsl, blur_frag_glsl);
      if (!shader_bloom) shader_bloom = std::make_unique<ppgso::Shader>(bloom_vert_glsl, bloom_frag_glsl);

      glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    // Initialize OpenGL state
    // Enable Z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable polygon culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    //shadows
      glGenFramebuffers(1, &depthMapFBO);

      glGenTextures(1, &depthMap);
      glBindTexture(GL_TEXTURE_2D, depthMap);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                   SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      float clampColor[]= {1.0f, 1.0f, 1.0f, 1.0f};
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

      glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
      glDrawBuffer(GL_NONE);
      glReadBuffer(GL_NONE);
      glBindFramebuffer(GL_FRAMEBUFFER, 0);


      glGenFramebuffers(1, &hdrFBO);
      glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

      glGenTextures(2, colorBuffers);
      for (unsigned int i = 0; i < 2; i++)
      {
          glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
          glTexImage2D(
                  GL_TEXTURE_2D, 0, GL_RGBA16F, SIZE, SIZE, 0, GL_RGBA, GL_FLOAT, NULL
          );
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
          // attach texture to framebuffer
          glFramebufferTexture2D(
                  GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0
          );
      }

      glGenRenderbuffers(1, &rboDepth);
      glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SIZE, SIZE);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

      glDrawBuffers(2, attachments);

      glGenFramebuffers(2, pingpongFBO);
      glGenTextures(2, pingpongColorbuffers);
      for (unsigned int i = 0; i < 2; i++)
      {
          glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
          glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SIZE, SIZE, 0, GL_RGBA, GL_FLOAT, NULL);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
          glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
          // also check if framebuffers are complete (no need for depth buffer)
          if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
              std::cout << "Framebuffer not complete!" << std::endl;
      }

  }

    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    void renderQuad()
    {
        if (quadVAO == 0)
        {
            float quadVertices[] = {
                    // positions        // texture Coords
                    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                    1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            };
            // setup plane VAO
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        }
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }



    void initScene() {
        scene.objects.clear();
        scene.scene_num++;
        srand(time(0));
//        scene.age = 30.0f;

//        scene.scene_num = 2;
//        scene.age = 98.0f;
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
            seagull->position = glm::vec3(25,30,10);
            seagull->rotation = glm::vec3((ppgso::PI/180)*(15), (ppgso::PI/180)*(-25), (ppgso::PI/180)*(-90));
////            seagull->position = seagull->keyframes[seagull->scene_num][0].position;
////            seagull->rotation = seagull->keyframes[seagull->scene_num][0].rotation;
            scene.objects.push_back(move(seagull));

            auto human = std::make_unique<Human>();
            human->age = scene.age;
            human->scene_num = scene.scene_num;
            human->position = human->keyframes[human->scene_num][0].position;
            human->rotation = human->keyframes[human->scene_num][0].rotation;
            scene.objects.push_back(move(human));

            auto boots = std::make_unique<Boots>();
            boots->age = scene.age;
            boots->scene_num = scene.scene_num;
            boots->position = boots->keyframes[boots->scene_num][0].position;
            boots->rotation = boots->keyframes[boots->scene_num][0].rotation;
            scene.objects.push_back(move(boots));

            auto eyes = std::make_unique<Eyes>();
            eyes->age = scene.age;
            eyes->scene_num = scene.scene_num;
            eyes->position = eyes->keyframes[eyes->scene_num][0].position;
            eyes->rotation = eyes->keyframes[eyes->scene_num][0].rotation;
            scene.objects.push_back(move(eyes));

            auto pants = std::make_unique<Pants>();
            pants->age = scene.age;
            pants->scene_num = scene.scene_num;
            pants->position = pants->keyframes[pants->scene_num][0].position;
            pants->rotation = pants->keyframes[pants->scene_num][0].rotation;
            scene.objects.push_back(move(pants));

            auto shirt = std::make_unique<Shirt>();
            shirt->age = scene.age;
            shirt->scene_num = scene.scene_num;
            shirt->position = shirt->keyframes[shirt->scene_num][0].position;
            shirt->rotation = shirt->keyframes[shirt->scene_num][0].rotation;
            scene.objects.push_back(move(shirt));

            scene.fallenCoconut = glm::linearRand(0.0f, 3.0f);
        }

        auto sky = std::make_unique<Sky>();
        sky->position = glm::vec3(0, 2, 0);
        sky->age = scene.age;
        sky->color = glm::vec3(0.541f, 0.796f, 0.898f);
        scene.objects.push_back(move(sky));

        auto sun = std::make_unique<Sphere>();
        sun->age = scene.age;
        sun->position = glm::vec3(0, 100, 0.0f);
        sun->scale *= 8;
        sun->color = glm::vec3({0.992f, 0.952f, 0.588f});
        scene.objects.push_back(move(sun));

        auto palmTree = std::make_unique<PalmTree>(scene);
        palmTree->age = scene.age;
        scene.palmTree_position = palmTree->position;
        palmTree->position = glm::vec3(-35,0,12);

        auto coconut1 = std::make_unique<Coconut>();
        coconut1->age = scene.age;
//        coconut->position = glm::vec3(-22,19,6);
        coconut1->position.x = palmTree->position.x + 13;
        coconut1->position.y = palmTree->position.y + 19;
        coconut1->position.z = palmTree->position.z + -6;

        auto coconut2 = std::make_unique<Coconut>();
        coconut2->age = scene.age;
        coconut2->position.x = palmTree->position.x + 11.7f;
        coconut2->position.y = palmTree->position.y + 19;
        coconut2->position.z = palmTree->position.z + -7.5f;

        auto coconut3 = std::make_unique<Coconut>();
        coconut3->age = scene.age;
        coconut3->position.x = palmTree->position.x + 14.3f;
        coconut3->position.y = palmTree->position.y + 19;
        coconut3->position.z = palmTree->position.z + -7.5f;

        if (scene.fallenCoconut <= 1.0) {
            coconut1->willMove = true;
            if (scene.scene_num == 2 && scene.coconut_position != glm::vec3{0, 0, 0}) {
                coconut1->position = scene.coconut_position;
                coconut1->rotation = scene.coconut_rotation;
            }
        }
        else if (scene.fallenCoconut <= 2.0) {
            coconut2->willMove = true;
            if (scene.scene_num == 2 && scene.coconut_position != glm::vec3{0, 0, 0}) {
                coconut2->position = scene.coconut_position;
                coconut2->rotation = scene.coconut_rotation;
            }
        }
        else {
            coconut3->willMove = true;
            if (scene.scene_num == 2 && scene.coconut_position != glm::vec3{0, 0, 0}) {
                coconut3->position = scene.coconut_position;
                coconut3->rotation = scene.coconut_rotation;
            }
        }

        auto palmLeaves = std::make_unique<PalmLeaves>();
        palmLeaves->age = scene.age;
        palmLeaves->position = palmTree->position;
        scene.objects.push_back(move(palmLeaves));

        scene.objects.push_back(move(coconut1));
        scene.objects.push_back(move(coconut2));
        scene.objects.push_back(move(coconut3));

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
        house->age = scene.age;
        house->scale *= 1.6;
        scene.objects.push_back(move(house));

        auto chimney = std::make_unique<Chimney>();
        chimney->age = scene.age;
        chimney->position = glm::vec3(62,15,10);
        scene.objects.push_back(move(chimney));

        // Add player to the scene
        auto island = std::make_unique<Island>();
        island->age = scene.age;
        island->position = glm::vec3(0,0,0);
        island->rotation.z = (ppgso::PI/180)*(-90);
        scene.objects.push_back(move(island));

        auto ocean = std::make_unique<Ocean>();
        ocean->age = scene.age;
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
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 300.0f);
        camera->age = scene.age;
        camera->scene_num = scene.scene_num;
        camera->position = camera->keyframes[camera->scene_num][0].position;
        camera->back = camera->keyframes[camera->scene_num][0].rotation;
        camera->keyframes[0][6].position.x = palmTree->position.x + 17;
        camera->keyframes[0][6].position.y = palmTree->position.y + 19;
        camera->keyframes[0][6].position.z = palmTree->position.z + 24;
        scene.camera = move(camera);
        scene.objects.push_back(move(palmTree));

    }

    void initInteriorScene() {
        scene.objects.clear();
        scene.scene_num++;
//        scene.age = 66.0f;

        //TODO: tiene

        //TODO: Detaily:
        //TODO: korytnacka sa netoci
        //TODO: obloha skareda
        //TODO: mozno lampa troska menej bloom
        //TODO: refaktor kodu

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

        auto fire = std::make_unique<Fire>();
        fire->position = glm::vec3(0, 0, 33);
        fire->rotation.x = (ppgso::PI / 180) * (-90);
        scene.objects.push_back(move(fire));

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

        auto boots = std::make_unique<Boots>();
        boots->age = scene.age;
        boots->scene_num = scene.scene_num;
        boots->position = boots->keyframes[boots->scene_num][0].position;
        boots->rotation = boots->keyframes[boots->scene_num][0].rotation;
        scene.objects.push_back(move(boots));

        auto eyes = std::make_unique<Eyes>();
        eyes->age = scene.age;
        eyes->scene_num = scene.scene_num;
        eyes->position = eyes->keyframes[eyes->scene_num][0].position;
        eyes->rotation = eyes->keyframes[eyes->scene_num][0].rotation;
        scene.objects.push_back(move(eyes));

        auto pants = std::make_unique<Pants>();
        pants->age = scene.age;
        pants->scene_num = scene.scene_num;
        pants->position = pants->keyframes[pants->scene_num][0].position;
        pants->rotation = pants->keyframes[pants->scene_num][0].rotation;
        scene.objects.push_back(move(pants));

        auto shirt = std::make_unique<Shirt>();
        shirt->age = scene.age;
        shirt->scene_num = scene.scene_num;
        shirt->position = shirt->keyframes[shirt->scene_num][0].position;
        shirt->rotation = shirt->keyframes[shirt->scene_num][0].rotation;
        scene.objects.push_back(move(shirt));

        auto spear = std::make_unique<Spear>();
        spear->age = scene.age;
        spear->scene_num = scene.scene_num;
        spear->position = spear->keyframes[spear->scene_num][0].position;
        spear->rotation = spear->keyframes[spear->scene_num][0].rotation;
        scene.objects.push_back(move(spear));

        auto seagull = std::make_unique<Seagull>();
        seagull->age = scene.age;
        seagull->scene_num = scene.scene_num;
        seagull->position = glm::vec3(0,0,0);
        seagull->rotation = glm::vec3((ppgso::PI/180)*(15), (ppgso::PI/180)*(-25), (ppgso::PI/180)*(-90));
//        seagull->position = seagull->keyframes[seagull->scene_num][0].position;
//        seagull->rotation = seagull->keyframes[seagull->scene_num][0].rotation;
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

      scene.update(dt);

      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // 1. render depth of scene to texture (from light's perspective)
      // --------------------------------------------------------------

      //glEnable(GL_DEPTH_TEST);

      glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
      glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      scene.renderDepth();
      glBindFramebuffer(GL_FRAMEBUFFER, 0);

      // reset viewport
      glViewport(0, 0, SIZE, SIZE);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



      glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    // Set gray background
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(.5f, .5f, .5f, 0);
      scene.render(depthMap);

      bool horizontal = true, first_iteration = true;
      unsigned int amount = 10;
      shader->use();
      for (unsigned int i = 0; i < amount; i++)
      {
          glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
          shader->setUniformInt("horizontal", horizontal);
          shader->setTexture("image", first_iteration ? (int)colorBuffers[1] : (int)pingpongColorbuffers[!horizontal]);
          //glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
          renderQuad();
          horizontal = !horizontal;
          if (first_iteration)
              first_iteration = false;
      }
      glBindFramebuffer(GL_FRAMEBUFFER, 0);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader_bloom->use();
      shader_bloom->setTexture("scene", (int)colorBuffers[0]);
      shader_bloom->setTexture("bloomBlur", (int)pingpongColorbuffers[!horizontal]);
      shader_bloom->setUniform("exposure", 1.0f);
      // Update and render all objects

      renderQuad();
  }
};

int main() {
    // Initialize our window
    SceneWindow window;
    window.initScene();
//    window.initInteriorScene();


//    window.scene.age = 45.0f;
    // Main execution loop


//    window.scene.age = 98.0;
//    window.scene.scene_num = 1;

//    window.scene.age = 50.0;
//    window.scene.scene_num = 0;




    while (window.pollEvents()) {
        if (window.scene.age >= 52.0f && window.scene.scene_num == 0){
            window.initInteriorScene();
        }
        if (window.scene.age >= 90.0f && window.scene.scene_num == 1){
            window.initScene();
        }
    }

    return EXIT_SUCCESS;
}
