#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "../Device/Device.hpp"
#include "../SwapChain/SwapChain.hpp"

namespace Vulkan::ImageViews
{
	std::vector<VkImage> GetImages();

	std::vector<VkImageView> GetImageViews();

	VkFormat GetSwapChainImageFormat();

	void SetSwapChainImageFormat(VkFormat format);

	VkExtent2D GetSwapChainExtent();

	void SetSwapChainExtent(VkExtent2D extent);

	void CreateImagesMemory(uint32_t *imageCount);

	void Create();

	void Destroy();
}
