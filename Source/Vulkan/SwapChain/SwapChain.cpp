#include "SwapChain.hpp"

VkSwapchainKHR s_SwapChain;
VkExtent2D     s_Extent;

/*----------------------------------------------------------------------------------------------------------*/
Vulkan::SwapChain::SwapChainSupportDetails
	Vulkan::SwapChain::QuerySwapChainSupport(VkPhysicalDevice device)
{
	const VkSurfaceKHR &surface = Surface::Get();

	SwapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	// Formats
	uint32_t formatsCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatsCount, nullptr);
	if (formatsCount != 0)
	{
		details.formats.resize(formatsCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device,
											 surface,
											 &formatsCount,
											 details.formats.data());
	}

	// Present Mode
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
	if (presentModeCount != 0)
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device,
												  surface,
												  &presentModeCount,
												  details.presentModes.data());
	}

	return details;
}

/*----------------------------------------------------------------------------------------------------------*/
VkSurfaceFormatKHR
	Vulkan::SwapChain::ChooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> formats)
{
	for (const auto &format : formats)
	{
		if (format.format == VK_FORMAT_B8G8R8A8_SRGB
			&& format.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
		{ return format; }
	}
	return formats[0];
}

/*----------------------------------------------------------------------------------------------------------*/
VkPresentModeKHR
	Vulkan::SwapChain::ChooseSwapPresentMode(std::vector<VkPresentModeKHR> presentModes)
{
	for (const auto &presentMode : presentModes)
	{
		if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR) return VK_PRESENT_MODE_MAILBOX_KHR;
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

/*----------------------------------------------------------------------------------------------------------*/
VkExtent2D Vulkan::SwapChain::ChooseSwapExtent(VkSurfaceCapabilitiesKHR capabilities)
{
	if (capabilities.currentExtent.width != UINT32_MAX) return capabilities.currentExtent;

	int width;
	int height;
	glfwGetFramebufferSize(Window::Get(), &width, &height);

	VkExtent2D actualExtent = {
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height),
	};

	actualExtent.width = std::max(capabilities.minImageExtent.width,
								  std::min(capabilities.maxImageExtent.width, actualExtent.width));
	actualExtent.height =
		std::max(capabilities.minImageExtent.height,
				 std::min(capabilities.maxImageExtent.height, actualExtent.height));

	return actualExtent;
}

/*----------------------------------------------------------------------------------------------------------*/
void Vulkan::SwapChain::Create()
{
	SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(Device::Physical::Get());

	VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR   presentMode   = ChooseSwapPresentMode(swapChainSupport.presentModes);
	s_Extent                         = ChooseSwapExtent(swapChainSupport.capabilities);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount
		&& imageCount > swapChainSupport.capabilities.maxImageCount)
	{ imageCount = swapChainSupport.capabilities.maxImageCount; }

	VkSwapchainCreateInfoKHR createInfo {};
	createInfo.minImageCount    = imageCount;
	createInfo.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.imageFormat      = surfaceFormat.format;
	createInfo.imageColorSpace  = surfaceFormat.colorSpace;
	createInfo.imageExtent      = s_Extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	createInfo.preTransform     = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha   = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode      = presentMode;
	createInfo.clipped          = VK_TRUE;
	createInfo.oldSwapchain     = VK_NULL_HANDLE;
	createInfo.surface          = Surface::Get();

	Queue::QueueFamilyIndex indices = Queue::FindQueueFamilies(Device::Physical::Get());
	uint32_t                queueFamilyIndices[] = { indices.graphicsFamily.value(),
                                      indices.presentFamily.value() };
	if (indices.graphicsFamily != indices.presentFamily)
	{
		createInfo.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices   = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices   = nullptr;
	}

	VkResult result =
		vkCreateSwapchainKHR(Device::Logical::Get(), &createInfo, nullptr, &s_SwapChain);
	if (result != VK_SUCCESS) { throw std::runtime_error("Failed to create SwapChain"); }

	ImageViews::SetSwapChainImageFormat(surfaceFormat.format);
	ImageViews::SetSwapChainExtent(s_Extent);
}

/*----------------------------------------------------------------------------------------------------------*/
VkSwapchainKHR Vulkan::SwapChain::Get() { return s_SwapChain; }

/*----------------------------------------------------------------------------------------------------------*/
void Vulkan::SwapChain::Destroy()
{
	vkDestroySwapchainKHR(Device::Logical::Get(), s_SwapChain, nullptr);
}

/*----------------------------------------------------------------------------------------------------------*/

VkExtent2D Vulkan::SwapChain::GetExtent() { return s_Extent; }

/*----------------------------------------------------------------------------------------------------------*/
