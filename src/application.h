#pragma once
#include "graphics/vulkan/vk_engine.h"

class Application {
public:
  const int WIDTH = 800;
  const int HEIGHT = 600;

private:
  struct GLFWwindow *_window;
  VulkanEngine _vulkanEngine;

public:
  void init();
  void cleanup();
  void run();

private:
  void initWindow();
  void initGraphics();
  void cleanupGraphics();
  void mainLoop();
};