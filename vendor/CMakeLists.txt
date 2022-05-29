cmake_minimum_required(VERSION 3.22)

add_subdirectory(vulkan)
add_subdirectory(stb_image)

#glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

set(GLFW_INCLUDE_DIR glfw/include)
#

#spdlog
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE spdlog/include)
#

#glm
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm/include)
#

#tinyobjloader
add_library(tinyobjloader STATIC)

target_sources(tinyobjloader PRIVATE
               tinyobjloader/tiny_obj_loader.h
               tinyobjloader/tiny_obj_loader.cc
               )

target_include_directories(tinyobjloader PUBLIC tinyobjloader)
#