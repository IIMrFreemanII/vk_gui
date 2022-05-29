#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "application.h"
#include "log.h"

void Application::init() {
  log::init();
  log::info("Application started!");

  initWindow();
  initGraphics();
}

void Application::cleanup() {
  cleanupGraphics();
  glfwDestroyWindow(_window);
  glfwTerminate();
}

void Application::run() {
  mainLoop();
}

void Application::initWindow() {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  _window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void Application::initGraphics() {
  _vulkanEngine.setWindow(_window);
  _vulkanEngine.init();
}

void Application::cleanupGraphics() {
  _vulkanEngine.cleanup();
}

void Application::mainLoop() {
  while (!glfwWindowShouldClose(_window)) {
    glfwPollEvents();
  }
}
