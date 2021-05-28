#pragma once

#include <iostream>
#include <vector>
#include <optional>
#include <vulkan/vulkan.h>
#include ".Surface/Surface.hpp"

namespace Vulkan::Queue
{
	struct QueueFamilyIndex
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isCompleted() { return graphicsFamily.has_value() && presentFamily.has_value(); }
	};

	QueueFamilyIndex FindQueueFamilies(VkPhysicalDevice device);

	VkQueue &GetPresentQueue();

	VkQueue &GetGraphicsQueue();
}
