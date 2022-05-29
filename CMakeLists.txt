cmake_minimum_required(VERSION 3.22)
project(vk_gui)

set(CMAKE_CXX_STANDARD 23)
message("CXX Standard: ${CMAKE_CXX_STANDARD}")

if (UNIX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif (WIN32)
    message("This is a Windows System")
endif ()

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/debug)
elseif (${CMAKE_BUILD_TYPE} MATCHES Release)
    set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/release)
endif ()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(ARCHIVE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

message("exe files ${EXECUTABLE_OUTPUT_PATH}")
message("lib files ${LIBRARY_OUTPUT_PATH}")
message("static lib files ${ARCHIVE_OUTPUT_PATH}")

message("CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

set(SOURCE_FILES
    src/main.cpp
    src/log.h
    src/log.cpp
    src/graphics/vulkan/vk_engine.h
    src/graphics/vulkan/vk_engine.cpp
    src/application.h
    src/application.cpp)

add_executable(vk_gui ${SOURCE_FILES})

add_subdirectory(vendor)

set(INCLUDE_DIR
    ${GLFW_INCLUDE_DIR})
target_include_directories(vk_gui PRIVATE ${INCLUDE_DIR})

#set(LIB_DIR
#    ${VULKAN_LIB_DIR})
#target_link_directories(vk_gui PUBLIC ${LIB_DIR})

set(LIB
    vulkan
    spdlog
    tinyobjloader
    glfw
    stb_image)
target_link_libraries(vk_gui ${LIB})
