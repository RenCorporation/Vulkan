#include "Vulkan/Vulkan.hpp"

void Cleanup()
{
	Vulkan::Window::Destroy();
	// All child objects created using instance must have been destroyed prior to destroying
	// instance
	Vulkan::Command::DestroyPool();
	Vulkan::Framebuffers::Destroy();
	Vulkan::GraphicsPipeline::Destroy();
	Vulkan::RenderPass::Destroy();
	Vulkan::ImageViews::Destroy();
	Vulkan::SwapChain::Destroy();
	Vulkan::Surface::Destroy();
	Vulkan::Device::Logical::Destroy();
	Vulkan::Instance::Destroy();
}

int main()
{
	Vulkan::Window::Create();
	Vulkan::Instance::Create();
	Vulkan::Surface::Create();

	Vulkan::Device::Physical::Pick();
	Vulkan::Device::Logical::Create();

	Vulkan::SwapChain::Create();
	Vulkan::ImageViews::Create();
	Vulkan::RenderPass::Create();
	Vulkan::GraphicsPipeline::Create();
	Vulkan::Framebuffers::Create();
	Vulkan::Command::CreatePool();
	Vulkan::Command::CreateBuffers();

	Vulkan::Window::MainLoop();

	Cleanup();
	return 0;
}
