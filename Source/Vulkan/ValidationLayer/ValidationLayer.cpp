#include "ValidationLayer.hpp"

bool                            s_EnableValidationLayers = true;
const std::vector<const char *> s_ValidationLayers       = { "VK_LAYER_KHRONOS_validation" };

/*----------------------------------------------------------------------------------------------------------*/
bool Vulkan::ValidationLayer::CheckSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers { layerCount };
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const auto &layer : s_ValidationLayers) {
		bool layerFound = false;
		for (const auto &availableLayer : availableLayers) {
			if (std::strcmp(layer, availableLayer.layerName) == 0) {
				layerFound = true;
				break;
			}
		}
		if (!layerFound) return false;
	}

	return true;
}

/*----------------------------------------------------------------------------------------------------------*/
std::vector<const char *> Vulkan::ValidationLayer::GetLayerNames() { return s_ValidationLayers; }

/*----------------------------------------------------------------------------------------------------------*/
bool Vulkan::ValidationLayer::IsEnabled() { return s_EnableValidationLayers; }

/*----------------------------------------------------------------------------------------------------------*/
