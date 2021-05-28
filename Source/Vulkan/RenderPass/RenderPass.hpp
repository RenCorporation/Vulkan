#pragma once

#include <vulkan/vulkan.h>
#include "../ImageView/ImageView.hpp"
#include "../Device/Device.hpp"

namespace Vulkan::RenderPass
{
	void Create();

    void Destroy();

	VkRenderPass Get();
}
