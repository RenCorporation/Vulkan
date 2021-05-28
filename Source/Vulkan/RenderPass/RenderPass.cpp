#include "RenderPass.hpp"

VkRenderPass s_RenderPass;

/*-----------------------------------------------------------------------------------------------*/
VkRenderPass Vulkan::RenderPass::Get() { return s_RenderPass; }

/*-----------------------------------------------------------------------------------------------*/
void Vulkan::RenderPass::Create()
{
	VkAttachmentDescription colorAttachment {};
	colorAttachment.format         = Vulkan::ImageViews::GetSwapChainImageFormat();
	colorAttachment.samples        = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass {};
	subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments    = &colorAttachmentRef;

	VkPipelineLayout pipelineLayout;

	VkRenderPassCreateInfo renderPassCreateInfo {};
	renderPassCreateInfo.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassCreateInfo.attachmentCount = 1;
	renderPassCreateInfo.pAttachments    = &colorAttachment;
	renderPassCreateInfo.subpassCount    = 1;
	renderPassCreateInfo.pSubpasses      = &subpass;

	VkResult result = vkCreateRenderPass(Vulkan::Device::Logical::Get(),
										 &renderPassCreateInfo,
										 nullptr,
										 &s_RenderPass);
	if (result != VK_SUCCESS) { throw std::runtime_error("Failed to create the render pass"); }
}

/*-----------------------------------------------------------------------------------------------*/
void Vulkan::RenderPass::Destroy()
{
	vkDestroyRenderPass(Vulkan::Device::Logical::Get(), s_RenderPass, nullptr);
}

/*-----------------------------------------------------------------------------------------------*/
