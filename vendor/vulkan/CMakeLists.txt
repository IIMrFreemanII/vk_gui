cmake_minimum_required(VERSION 3.22)

add_library(vulkan INTERFACE)
target_include_directories(vulkan INTERFACE include)

if (UNIX)
    message("Vulkan - using macos libs")
    target_link_directories(vulkan INTERFACE lib/macos)
elseif (WIN32)
    message("Vulkan - using win32 libs")
    target_link_directories(vulkan INTERFACE lib/win32)
endif ()

target_link_libraries(vulkan INTERFACE libvulkan.1.dylib libvulkan.1.3.211.dylib)
