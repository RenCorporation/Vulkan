#include "Extensions.hpp"

std::vector<const char *> s_Extensions { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

/*----------------------------------------------------------------------------------------------------------*/
std::vector<const char *> Vulkan::Extensions::GetRequiredExtensions()
{
	uint32_t     glfwExtensionCount = 0;
	const char **glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (ValidationLayer::IsEnabled()) { extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME); }

	return extensions;
}

/*----------------------------------------------------------------------------------------------------------*/
std::vector<const char *> Vulkan::Extensions::GetEnabledExtensions() { return s_Extensions; }

/*----------------------------------------------------------------------------------------------------------*/
bool Vulkan::Extensions::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> availableExtensions;
	vkEnumerateDeviceExtensionProperties(device,
										 nullptr,
										 &extensionCount,
										 availableExtensions.data());

	auto                  deviceExtensions = GetEnabledExtensions();
	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto &extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

/*----------------------------------------------------------------------------------------------------------*/
