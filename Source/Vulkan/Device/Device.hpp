#pragma once

#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

#include "../Queue/Queue.hpp"
#include "../Instance/Instance.hpp"
#include "../Extensions/Extensions.hpp"
#include "../SwapChain/SwapChain.hpp"

namespace Vulkan::Device::Physical
{
	int RateDeviceSuitability(const VkPhysicalDevice &device);

	VkPhysicalDevice Pick();

	VkPhysicalDevice Get();
}

namespace Vulkan::Device::Logical
{
	VkDevice Create();

	void Destroy();

	VkDevice Get();
}
