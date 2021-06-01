#pragma once

#include <vulkan/vulkan.h>
#include "../Shader/Shader.hpp"
#include "../SwapChain/SwapChain.hpp"
#include "../RenderPass/RenderPass.hpp"

namespace Vulkan::GraphicsPipeline
{
	void Create();

	VkPipeline Get();

	VkPipelineLayout GetLayout();

	void Destroy();
}
