#pragma once

#include "vector"
#include "deque"

#include "vulkan/vulkan.h"

class DeletionQueue {
  std::deque<std::function<void()>> deletors;

public:
  void push_function(std::function<void()> &&function) {
    deletors.push_front(function);
  }

  void flush() {
    for (const auto &func: deletors) {
      func();
    }

    deletors.clear();
  }
};

class VulkanEngine {
  struct GLFWwindow* _window;

public:
  void init();
  void cleanup();

  void setWindow(GLFWwindow* window) {
    this->_window = window;
  }

private:
#ifdef NDEBUG
  const bool _enableValidationLayers = false;
#else
  const bool _enableValidationLayers = true;
#endif

  std::vector<const char*> _validationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };
  std::vector<const char*> _deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    "VK_KHR_portability_subset"
  };
  std::vector<const char*> _instanceExtensions = {
    "VK_KHR_get_physical_device_properties2",
  };
  DeletionQueue _deletionQueue;
  VkInstance _instance;

private:
  void createInstance();

  bool checkValidationLayerSupport();
};