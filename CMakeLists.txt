cmake_minimum_required(VERSION 3.16)
project(VulkanTutorial)
set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
link_libraries(${Vulkan_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_STATIC_LIBRARIES})

find_package(glm REQUIRED)
message(${CMAKE_SOURCE_DIR})

add_executable(VulkanTutorial Source/main.cpp
                              Source/Vulkan/Vulkan.hpp
                              Source/Vulkan/Window/Window.cpp Source/Vulkan/Window/Window.hpp
                              Source/Vulkan/Instance/Instance.cpp Source/Vulkan/Instance/Instance.hpp
                              Source/Vulkan/ValidationLayer/ValidationLayer.cpp Source/Vulkan/ValidationLayer/ValidationLayer.hpp
                              Source/Vulkan/Extensions/Extensions.cpp Source/Vulkan/Extensions/Extensions.hpp
                              Source/Vulkan/Surface/Surface.cpp Source/Vulkan/Surface/Surface.hpp
                              Source/Vulkan/Device/Device.cpp Source/Vulkan/Device/Device.hpp
                              Source/Vulkan/Queue/Queue.cpp Source/Vulkan/Queue/Queue.hpp
                              Source/Vulkan/SwapChain/SwapChain.cpp Source/Vulkan/SwapChain/SwapChain.hpp
                              Source/Vulkan/ImageView/ImageView.cpp Source/Vulkan/ImageView/ImageView.hpp
                              Source/Vulkan/GraphicsPipeline/GraphicsPipeline.cpp Source/Vulkan/GraphicsPipeline/GraphicsPipeline.hpp
                              Source/Vulkan/Shader/Shader.cpp Source/Vulkan/Shader/Shader.hpp
                              Source/Vulkan/RenderPass/RenderPass.cpp Source/Vulkan/RenderPass/RenderPass.hpp
                              Source/Vulkan/Framebuffers/Framebuffers.cpp Source/Vulkan/Framebuffers/Framebuffers.hpp
                              Source/Vulkan/CommandBuffers/CommandBuffers.cpp Source/Vulkan/CommandBuffers/CommandBuffers.hpp
)
