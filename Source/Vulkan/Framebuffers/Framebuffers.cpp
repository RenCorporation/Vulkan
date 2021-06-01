#include "Framebuffers.hpp"

std::vector<VkFramebuffer> s_SwapChainFrameBuffers;

/*-----------------------------------------------------------------------------------------------*/
std::vector<VkFramebuffer> Vulkan::Framebuffers::Get() { return s_SwapChainFrameBuffers; }

/*-----------------------------------------------------------------------------------------------*/
void Vulkan::Framebuffers::Create()
{
	s_SwapChainFrameBuffers.resize(ImageViews::GetImageViews().size());

	for (size_t i = 0; i < ImageViews::GetImageViews().size(); i++)
	{
		VkImageView attachments[] = { ImageViews::GetImageViews()[i] };

		VkFramebufferCreateInfo framebufferCreateInfo {};
		framebufferCreateInfo.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCreateInfo.renderPass      = RenderPass::Get();
		framebufferCreateInfo.attachmentCount = 1;
		framebufferCreateInfo.pAttachments    = attachments;
		framebufferCreateInfo.width           = SwapChain::GetExtent().width;
		framebufferCreateInfo.height          = SwapChain::GetExtent().height;
		framebufferCreateInfo.layers          = 1;

		VkResult result = vkCreateFramebuffer(Device::Logical::Get(),
											  &framebufferCreateInfo,
											  nullptr,
											  &s_SwapChainFrameBuffers[i]);
		if (result != VK_SUCCESS) { throw std::runtime_error("Cannot create framebuffer"); }
	}
}

/*-----------------------------------------------------------------------------------------------*/
void Vulkan::Framebuffers::Destroy()
{
	for (auto frambuffer : s_SwapChainFrameBuffers)
	{
		vkDestroyFramebuffer(Device::Logical::Get(), frambuffer, nullptr);
	}
}

/*-----------------------------------------------------------------------------------------------*/
