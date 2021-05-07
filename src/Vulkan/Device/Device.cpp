#include "Device.hpp"

VkDevice         s_Device;
VkPhysicalDevice s_PhysicalDevice = VK_NULL_HANDLE;

/*---------------------------------------------------------------------------------------------------------**/
int Vulkan::Device::Physical::RateDeviceSuitability(const VkPhysicalDevice &device) {
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures   deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	int score = 0;

	// Essential Capabilities
	if (!deviceFeatures.geometryShader) return 0;
	if (!Queue::FindQueueFamilies(device).isCompleted()) return 0;
	if (Extensions::CheckDeviceExtensionSupport(device)) return 0;
	SwapChain::SwapChainSupportDetails swapChainSupport = SwapChain::QuerySwapChainSupport(device);
	if (swapChainSupport.formats.empty() || swapChainSupport.presentModes.empty()) return 0;

	// Preferable Capabilities
	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) score += 1;
	if (Queue::FindQueueFamilies(device).isCompleted()) score += 1;
	score += deviceProperties.limits.maxImageDimension2D;

	return score;
}

/*---------------------------------------------------------------------------------------------------------**/
VkPhysicalDevice Vulkan::Device::Physical::Pick() {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(Instance::Get(), &deviceCount, nullptr);

	if (deviceCount == 0) throw std::runtime_error("No GPUs with Vulkan Support!");

	std::vector<VkPhysicalDevice> physicalDevices { deviceCount };
	vkEnumeratePhysicalDevices(Instance::Get(), &deviceCount, physicalDevices.data());

	std::multimap<int, VkPhysicalDevice> scores;
	for (const auto &device : physicalDevices) {
		int score = RateDeviceSuitability(device);
		scores.insert(std::make_pair(score, device));
	}

	if (scores.rbegin()->first > 0) s_PhysicalDevice = scores.rbegin()->second;
	else
		throw std::runtime_error("No GPU with Vulkan Support");

	return s_PhysicalDevice;
}

/*---------------------------------------------------------------------------------------------------------**/
VkPhysicalDevice Vulkan::Device::Physical::Get() { return s_PhysicalDevice; }

/*---------------------------------------------------------------------------------------------------------**/
VkDevice Vulkan::Device::Logical::Create() {
	Queue::QueueFamilyIndex              indices       = Queue::FindQueueFamilies(Physical::Get());
	float                                queuePriority = 1.0f;
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t>                   uniqueQueueFamilies = {
        indices.graphicsFamily.value(),
        indices.presentFamily.value(),
	};
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo {};
		queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
		queueCreateInfo.queueCount       = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		queueCreateInfos.push_back(queueCreateInfo);
	}

	const auto               enabledExtensions = Extensions::GetEnabledExtensions();
	VkPhysicalDeviceFeatures deviceFeatures {};
	VkDeviceCreateInfo       deviceCreateInfo {};
	deviceCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pEnabledFeatures        = &deviceFeatures;
	deviceCreateInfo.queueCreateInfoCount    = queueCreateInfos.size();
	deviceCreateInfo.pQueueCreateInfos       = queueCreateInfos.data();
	deviceCreateInfo.enabledExtensionCount   = enabledExtensions.size();
	deviceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();

	VkResult result = vkCreateDevice(Physical::Get(), &deviceCreateInfo, nullptr, &s_Device);
	if (result != VK_SUCCESS) throw std::runtime_error("Couldn't create Logical Device");

	vkGetDeviceQueue(s_Device, indices.graphicsFamily.value(), 0, &Queue::GetGraphicsQueue());
	vkGetDeviceQueue(s_Device, indices.presentFamily.value(), 0, &Queue::GetPresentQueue());

	return s_Device;
}

/*---------------------------------------------------------------------------------------------------------**/
VkDevice Vulkan::Device::Logical::Get() { return s_Device; }

/*---------------------------------------------------------------------------------------------------------**/
void Vulkan::Device::Logical::Destroy() { vkDestroyDevice(s_Device, nullptr); }

/*---------------------------------------------------------------------------------------------------------**/
