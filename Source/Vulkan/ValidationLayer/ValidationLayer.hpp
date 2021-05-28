#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <vulkan/vulkan.h>

namespace Vulkan::ValidationLayer
{
	bool CheckSupport();

	std::vector<const char *> GetLayerNames();

	bool IsEnabled();
}
