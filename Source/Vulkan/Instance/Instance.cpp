#include "Instance.hpp"
#include "../Extensions/Extensions.hpp"

VkInstance s_Instance = nullptr;

/*------------------------------------------------------------------------------------------------*/
VkInstance Vulkan::Instance::Create()
{
	if (ValidationLayer::IsEnabled() && !ValidationLayer::CheckSupport())
	{ throw std::runtime_error("Desired validation layer not found"); }

	auto layers     = ValidationLayer::GetLayerNames();
	auto extensions = Extensions::GetRequiredExtensions();

	VkApplicationInfo applicationInfo {};
	applicationInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pApplicationName   = "Hello Triangle";
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pEngineName        = "No Engine";
	applicationInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.apiVersion         = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceCreateInfo {};
	instanceCreateInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo        = &applicationInfo;
	instanceCreateInfo.enabledLayerCount       = layers.size();
	instanceCreateInfo.ppEnabledLayerNames     = layers.data();
	instanceCreateInfo.enabledExtensionCount   = extensions.size();
	instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

	VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &s_Instance);
	if (result != VK_SUCCESS) throw std::runtime_error("Failed to create Vulkan instance");
	return s_Instance;
}

/*------------------------------------------------------------------------------------------------*/
VkInstance Vulkan::Instance::Get() { return s_Instance; }

/*------------------------------------------------------------------------------------------------*/
void Vulkan::Instance::Destroy() { vkDestroyInstance(s_Instance, nullptr); }

/*------------------------------------------------------------------------------------------------*/
