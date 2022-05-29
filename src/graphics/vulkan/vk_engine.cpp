#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include "vk_engine.h"
#include "../../log.h"

void VulkanEngine::init() {
  createInstance();
}

void VulkanEngine::cleanup() {
  _deletionQueue.flush();
}

void VulkanEngine::createInstance() {
  if (_enableValidationLayers && !checkValidationLayerSupport()) {
    log::error("validation layers requested, but not available!");
  }

  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  log::info("glfwGetRequiredInstanceExtensions {}", glfwExtensionCount);
  for (int i = 0; i < glfwExtensionCount; ++i) {
    const char* extensionName = *(glfwExtensions + i);
    _instanceExtensions.push_back(extensionName);
    log::info("- {}", extensionName);
  }

  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = _instanceExtensions.size();
  createInfo.ppEnabledExtensionNames = _instanceExtensions.data();
  if (_enableValidationLayers) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
    createInfo.ppEnabledLayerNames = _validationLayers.data();
  } else {
    createInfo.enabledLayerCount = 0;
  }

  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  log::info("vkEnumerateInstanceExtensionProperties {}:", extensionCount);
  std::vector<VkExtensionProperties> extensions{extensionCount};
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
  for (const auto &extension: extensions) {
    log::info("- {}", extension.extensionName);
  }

  VK_CHECK(vkCreateInstance(&createInfo, nullptr, &_instance));

  _deletionQueue.push_function(
    [=]() {
      vkDestroyInstance(_instance, nullptr);
    }
  );
}

bool VulkanEngine::checkValidationLayerSupport() {
  uint32_t layerCount = 0;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  log::info("vkEnumerateInstanceLayerProperties {}", layerCount);

  std::vector<VkLayerProperties> availableLayers{layerCount};
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const auto &layer: availableLayers) {
    log::info("- {}", layer.layerName);
  }

  for (const char* layerName: _validationLayers) {
    bool layerFound = false;

    for (const auto &layerProperties: availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}
