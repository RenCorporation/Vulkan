#include "ImageView.hpp"

std::vector<VkImage>     s_SwapChainImages;
std::vector<VkImageView> s_SwapChainImageViews;
VkFormat                 s_SwapChainImageFormat;
VkExtent2D               s_SwapChainExtent;

/*------------------------------------------------------------------------------------------------*/
std::vector<VkImage> Vulkan::ImageViews::GetImages() { return s_SwapChainImages; }

/*------------------------------------------------------------------------------------------------*/
std::vector<VkImageView> Vulkan::ImageViews::GetImageViews() { return s_SwapChainImageViews; }

/*------------------------------------------------------------------------------------------------*/
VkFormat Vulkan::ImageViews::GetSwapChainImageFormat() { return s_SwapChainImageFormat; }

/*------------------------------------------------------------------------------------------------*/
void Vulkan::ImageViews::SetSwapChainImageFormat(VkFormat format)
{
	s_SwapChainImageFormat = format;
}

/*------------------------------------------------------------------------------------------------*/
VkExtent2D Vulkan::ImageViews::GetSwapChainExtent() { return s_SwapChainExtent; }

/*------------------------------------------------------------------------------------------------*/
void Vulkan::ImageViews::SetSwapChainExtent(VkExtent2D extent) { s_SwapChainExtent = extent; }

/*------------------------------------------------------------------------------------------------*/
void Vulkan::ImageViews::CreateImagesMemory(uint32_t *imageCount)
{
	s_SwapChainImages.resize(*imageCount);
	vkGetSwapchainImagesKHR(Device::Logical::Get(),
							SwapChain::Get(),
							imageCount,
							s_SwapChainImages.data());
}

/*------------------------------------------------------------------------------------------------*/
void Vulkan::ImageViews::Destroy()
{
	for (auto imageView : Vulkan::ImageViews::GetImageViews())
	{
		vkDestroyImageView(Device::Logical::Get(), imageView, nullptr);
	}
}

/*------------------------------------------------------------------------------------------------*/
void Vulkan::ImageViews::Create()
{
	s_SwapChainImageViews.resize(s_SwapChainImages.size());

	for (size_t i = 0; i < s_SwapChainImages.size(); i++)
	{
		VkImageViewCreateInfo createInfo {};
		createInfo.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image                           = s_SwapChainImages[i];
		createInfo.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format                          = s_SwapChainImageFormat;
		createInfo.components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.levelCount     = 1;
		createInfo.subresourceRange.layerCount     = 1;
		createInfo.subresourceRange.baseMipLevel   = 0;
		createInfo.subresourceRange.baseArrayLayer = 0;

		VkResult result = vkCreateImageView(Device::Logical::Get(),
											&createInfo,
											nullptr,
											&s_SwapChainImageViews[i]);
		if (result != VK_SUCCESS) { throw std::runtime_error("Failed to create Image View"); }
	}
}

/*------------------------------------------------------------------------------------------------*/
