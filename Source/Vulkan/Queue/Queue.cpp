#include "Queue.hpp"

VkQueue s_PresentQueue;
VkQueue s_GraphicsQueue;

/*----------------------------------------------------------------------------------------------------------*/
Vulkan::Queue::QueueFamilyIndex Vulkan::Queue::FindQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndex indices;

	uint32_t queueFamilyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamily { queueFamilyCount };
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamily.data());

	int i = 0;
	for (const auto &queueFamily : queueFamily)
	{
		// Check for graphics queue support on the GPU.
		if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) indices.graphicsFamily = i;

		// Check for presentation queue support on the GPU.
		VkBool32 presentQueueSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, Surface::Get(), &presentQueueSupport);
		if (presentQueueSupport) indices.presentFamily = i;

		// Check if both queues are present.
		if (indices.isCompleted()) break;
		i++;
	}

	return indices;
}

/*----------------------------------------------------------------------------------------------------------*/
VkQueue &Vulkan::Queue::GetPresentQueue() { return s_PresentQueue; }

/*----------------------------------------------------------------------------------------------------------*/
VkQueue &Vulkan::Queue::GetGraphicsQueue() { return s_GraphicsQueue; }

/*----------------------------------------------------------------------------------------------------------*/
