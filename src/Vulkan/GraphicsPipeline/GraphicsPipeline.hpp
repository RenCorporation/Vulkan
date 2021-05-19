#pragma once

#include <vulkan/vulkan.h>
#include "../Shader/Shader.hpp"
#include "../SwapChain/SwapChain.hpp"

namespace Vulkan::GraphicsPipeline {
	void Create();

	VkPipelineLayout Get();

	void Destroy();
}
