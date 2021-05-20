#include "Surface.hpp"
#include "../Instance/Instance.hpp"
#include "../Window/Window.hpp"

VkSurfaceKHR s_Surface;

/*----------------------------------------------------------------------------------------------------------*/
void Vulkan::Surface::Create() {
	VkResult result = glfwCreateWindowSurface(Instance::Get(), Window::Get(), nullptr, &s_Surface);
	if (result != VK_SUCCESS) throw std::runtime_error("Failed to create window surface");
}

/*----------------------------------------------------------------------------------------------------------*/
VkSurfaceKHR Vulkan::Surface::Get() { return s_Surface; }

/*----------------------------------------------------------------------------------------------------------*/
void Vulkan::Surface::Destroy() {
	vkDestroySurfaceKHR(Vulkan::Instance::Get(), Vulkan::Surface::Get(), nullptr);
}

/*----------------------------------------------------------------------------------------------------------*/
