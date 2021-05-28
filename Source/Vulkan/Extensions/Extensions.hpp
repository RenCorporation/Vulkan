#pragma once
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include ".ValidationLayer/ValidationLayer.hpp"

namespace Vulkan::Extensions
{
	std::vector<const char *> GetRequiredExtensions();

	std::vector<const char *> GetEnabledExtensions();

	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
}
