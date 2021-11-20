#include "player.h"
#include "scene.h"
#include "asteroid.h"
#include "projectile.h"
#include "explosion.h"
#include "spear.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Player::mesh;
std::unique_ptr<ppgso::Texture> Player::texture;
std::unique_ptr<ppgso::Shader> Player::shader;

Player::Player() {
  // Scale the default model
  scale *= 3.0f;
  rotation.z = ppgso::PI/2.0f;
  rotation.x = (ppgso::PI/180.0f)*(15);;
  rotation.y = (ppgso::PI/180.0f)*(-25);
  // Initialize static resources if needed
  if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
  if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("seagullTexture.bmp"));
  if (!mesh) mesh = std::make_unique<ppgso::Mesh>("seagull-low-poly.obj");
}

bool Player::update(Scene &scene, float dt) {
  // Fire delay increment
    std::cout<< " z vtacik: "<< position.z<< std::endl;
    std::cout<< " y vtacik: "<< position.y<< std::endl;
    std::cout<< " x vtacik: "<< position.x<< std::endl;
    std::cout<<age<< " cas:"<< std::endl;
    std::cout<<dt<< " dt:"<< std::endl;
  fireDelay += dt;
  age += dt;
  scene.camera->position.x = position.x;
  scene.camera->position.y = position.y;
    for ( auto& obj : scene.objects ) {
        if (obj.get() == this)
            continue;

        // We only need to collide with asteroids, ignore other objects
        auto spear = dynamic_cast<Spear *>(obj.get());
        if (!spear) continue;
        if (!(distance(position, spear->position) < spear->scale.y * 3)) {
            position.x += 10 * dt;
            position.y -= 2 * dt;
        }
        }
//  else if(age > 5 && age < 10){
////      position.y += 10 * dt;
//      if (rotation.y == ppgso::PI / -2.0f) {
////          rotation.y = ppgso::PI / -1.0f;
//      }
//  }
//  }

//  // Keyboard controls
//  if(scene.keyboard[GLFW_KEY_LEFT]) {
//    position.x += 10 * dt;
//    rotation.y = ppgso::PI/-2.0f;
//  } else if(scene.keyboard[GLFW_KEY_RIGHT]) {
//    position.x -= 10 * dt;
//    rotation.y = ppgso::PI/2.0f;
//  }
//  else {
//    rotation.z = 0;
//  }

  // Firing projectiles
  if(scene.keyboard[GLFW_KEY_SPACE] && fireDelay > fireRate) {
    // Reset fire delay
    fireDelay = 0;
    // Invert file offset
    fireOffset = -fireOffset;

    auto projectile = std::make_unique<Projectile>();
    projectile->position = position + glm::vec3(0.0f, 0.0f, 0.3f) + fireOffset;
    scene.objects.push_back(move(projectile));
  }

  generateModelMatrix();
  return true;
}

void Player::render(Scene &scene) {
  shader->use();

  // Set up light
  shader->setUniform("LightDirection", scene.lightDirection);

  // use camera
  shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
  shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

  // render mesh
  shader->setUniform("ModelMatrix", modelMatrix);
  shader->setUniform("Texture", *texture);
  mesh->render();
}

void Player::onClick(Scene &scene) {
  std::cout << "Player has been clicked!" << std::endl;
}
