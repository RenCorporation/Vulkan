#include "Shader.hpp"

std::vector<char> Vulkan::Shader::ReadFile(const std::string &fileName) {
	std::ifstream file(fileName, std::ios::ate | std::ios::binary);
	if (!file.is_open()) throw std::runtime_error("Unable to open shader" + fileName);

	size_t fileSize = (size_t)file.tellg();

	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

VkShaderModule Vulkan::Shader::CreateShader(const std::vector<char> &code) {
	VkShaderModuleCreateInfo shaderModuleCreateInfo {};
	shaderModuleCreateInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderModuleCreateInfo.codeSize = code.size();
	shaderModuleCreateInfo.pCode    = reinterpret_cast<const uint32_t *>(code.data());

	VkShaderModule shaderModule;
	VkResult       result =
		vkCreateShaderModule(Vulkan::Device::Logical::Get(), &shaderModuleCreateInfo, nullptr, &shaderModule);
	if (result != VK_SUCCESS) { throw std::runtime_error("Failed to Create Shader Module"); }

	return shaderModule;
}
