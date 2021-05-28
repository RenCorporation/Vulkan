#pragma once
#include <iostream>
#include <vulkan/vulkan.h>

namespace Vulkan::Surface
{
	void Create();

	VkSurfaceKHR Get();

	void Destroy();
}
