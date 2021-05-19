cmake_minimum_required(VERSION 3.19)
project(VulkanTutorial)

find_package(Vulkan REQUIRED)
link_libraries(${Vulkan_LIBRARIES})

find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_STATIC_LIBRARIES})

find_package(glm REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(VulkanTutorial src/main.cpp src/Vulkan/Window/Window.cpp src/Vulkan/Window/Window.hpp src/Vulkan/Instance/Instance.cpp src/Vulkan/Instance/Instance.hpp src/Vulkan/ValidationLayer/ValidationLayer.cpp src/Vulkan/ValidationLayer/ValidationLayer.hpp src/Vulkan/Extensions/Extensions.cpp src/Vulkan/Extensions/Extensions.hpp src/Vulkan/Surface/Surface.cpp src/Vulkan/Surface/Surface.hpp src/Vulkan/Device/Device.cpp src/Vulkan/Device/Device.hpp src/Vulkan/Queue/Queue.cpp src/Vulkan/Queue/Queue.hpp src/Vulkan/Vulkan.h src/Vulkan/SwapChain/SwapChain.cpp src/Vulkan/SwapChain/SwapChain.hpp src/Vulkan/ImageView/ImageView.cpp src/Vulkan/ImageView/ImageView.hpp src/Vulkan/GraphicsPipeline/GraphicsPipeline.cpp src/Vulkan/GraphicsPipeline/GraphicsPipeline.hpp src/Vulkan/Shader/Shader.cpp src/Vulkan/Shader/Shader.hpp)
