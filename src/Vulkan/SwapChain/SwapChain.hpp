#pragma once
#include <vector>
#include <limits>
#include <algorithm>
#include <vulkan/vulkan.h>
#include "../Queue/Queue.hpp"
#include "../Window/Window.hpp"
#include "../Device/Device.hpp"
#include "../Surface/Surface.hpp"
#include "../ImageView/ImageView.hpp"

namespace Vulkan::SwapChain {
	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR        capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR>   presentModes;
	};

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> formats);

	VkPresentModeKHR ChooseSwapPresentMode(std::vector<VkPresentModeKHR> presentModes);

	VkExtent2D ChooseSwapExtent(VkSurfaceCapabilitiesKHR capabilities);

	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

	void Create();

	VkSwapchainKHR Get();

	void Destroy();
}
