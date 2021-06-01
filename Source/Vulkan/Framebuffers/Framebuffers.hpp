#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "../ImageView/ImageView.hpp"
#include "../RenderPass/RenderPass.hpp"
#include "../SwapChain/SwapChain.hpp"
#include "../Device/Device.hpp"

namespace Vulkan::Framebuffers
{
	std::vector<VkFramebuffer> Get();

	void Create();

	void Destroy();
}
