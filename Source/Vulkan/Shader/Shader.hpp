#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <vulkan/vulkan.h>
#include "../Device/Device.hpp"

namespace Vulkan::Shader
{
	std::vector<char> ReadFile(const std::string &fileName);

	VkShaderModule CreateShader(const std::vector<char> &code);
}
