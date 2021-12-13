#include <cstdlib>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

bool ppgso::Window::pollEvents() {
  onIdle();
  glfwSwapBuffers(window);
  glfwPollEvents();
  return !glfwWindowShouldClose(window);
}

ppgso::Window::Window(std::string title, int width, int height) : title{title}, width{width}, height{height} {
  // Set up glfw
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //prebublat


    glfwInstance::Init();

  glfwSetErrorCallback(glfw_error_callback);

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef NDEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window)
    throw std::runtime_error("Failed to initialize GLFW Window!");

  glfwSetKeyCallback(window, glfw_key_callback);
  glfwSetCursorPosCallback(window, glfw_cursor_pos_callback);
  glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
  glfwSetWindowRefreshCallback(window, glfw_window_refresh_callback);

  glfwMakeContextCurrent(window);

  // Initialize glew
  glewInstance::Init();

  windows.insert({window, this});

#ifndef NDEBUG
  // Basic OpenGL information to print
  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif
}

ppgso::Window::~Window() {
  windows.erase(window);
  glfwDestroyWindow(window);
}

void ppgso::Window::glfw_key_callback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) windows[window]->close();

  windows[window]->onKey(key, scanCode, action, mods);
}

void ppgso::Window::glfw_error_callback(int error, const char *description) {
  std::stringstream msg;
  msg << "GLFW Error " << error << " : " << std::string{description} << std::endl;

  std::cerr << msg.str() << std::endl;

  throw std::runtime_error(msg.str());
}

void ppgso::Window::resetViewport() {
  int fbWidth, fbHeight;
  glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);
}

void ppgso::Window::showCursor() {
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void ppgso::Window::hideCursor() {
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void ppgso::Window::glfw_cursor_pos_callback(GLFWwindow *window, double cursorX, double cursorY) {
  windows[window]->onCursorPos(cursorX, cursorY);
}

void ppgso::Window::glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
  windows[window]->onMouseButton(button, action, mods);
}

void ppgso::Window::close() {
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void ppgso::Window::glfw_window_refresh_callback(GLFWwindow *window) {
  windows[window]->onRefresh();
}

void ppgso::Window::resize(int width, int height) {
  glfwSetWindowSize(window, width, height);
}

ppgso::Window::glewInstance& ppgso::Window::glewInstance::Init() {
  static glewInstance instance;
  return instance;
}

ppgso::Window::glewInstance::glewInstance() {
  glewExperimental = GL_TRUE;
  glewInit();

  if (!glewIsSupported("GL_VERSION_3_3"))
    throw std::runtime_error("Failed to initialize GLEW with OpenGL 3.3!");
}

// Store window instances for callbacks
std::map<GLFWwindow *, ppgso::Window *> ppgso::Window::windows;

ppgso::Window::glfwInstance::glfwInstance() {
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW!");
}

ppgso::Window::glfwInstance::~glfwInstance() {
  glfwTerminate();
}

ppgso::Window::glfwInstance& ppgso::Window::glfwInstance::Init() {
  static glfwInstance instance;
  return instance;
}

void ppgso::Window::fpsLimit(bool limit) {
  if(limit) glfwSwapInterval(1);
  glfwSwapInterval(0);
}
