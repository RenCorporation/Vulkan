#pragma once

#include <vulkan/vulkan.h>

namespace Vulkan::Instance
{
	VkInstance Create();

	VkInstance Get();

	void Destroy();
}
