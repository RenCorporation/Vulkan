#include "Command.hpp"

VkCommandPool                s_CommandPool;
std::vector<VkCommandBuffer> s_CommandBuffers;

/*-----------------------------------------------------------------------------------------------*/
void Vulkan::Command::CreatePool()
{
	Queue::QueueFamilyIndex queueFamilyIndices = Queue::FindQueueFamilies(Device::Physical::Get());

	VkCommandPoolCreateInfo poolCreateInfo {};
	poolCreateInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolCreateInfo.flags            = 0;
	poolCreateInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

	VkResult result =
		vkCreateCommandPool(Device::Logical::Get(), &poolCreateInfo, nullptr, &s_CommandPool);
	if (result != VK_SUCCESS) { throw std::runtime_error("Cannot create Command Pool"); }
}

/*-----------------------------------------------------------------------------------------------*/
void Vulkan::Command::DestroyPool()
{
	vkDestroyCommandPool(Device::Logical::Get(), s_CommandPool, nullptr);
}

/*-----------------------------------------------------------------------------------------------*/
void Vulkan::Command::CreateBuffers()
{
    s_CommandBuffers.resize(Framebuffers::Get().size());

	VkCommandBufferAllocateInfo commandBufferAllocInfo {};
	commandBufferAllocInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferAllocInfo.commandPool        = s_CommandPool;
	commandBufferAllocInfo.commandBufferCount = (uint32_t)s_CommandBuffers.size();

	VkResult result = vkAllocateCommandBuffers(Device::Logical::Get(),
											   &commandBufferAllocInfo,
											   s_CommandBuffers.data());
	if (result != VK_SUCCESS) { throw std::runtime_error("Cannot allocate command buffers"); }

	for (size_t i = 0; i < s_CommandBuffers.size(); i++)
	{
		VkCommandBufferBeginInfo beginInfo {};
		beginInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags            = 0;
		beginInfo.pInheritanceInfo = nullptr;

		VkResult bufferBeginResult = vkBeginCommandBuffer(s_CommandBuffers[i], &beginInfo);
		if (bufferBeginResult != VK_SUCCESS)
		{ throw std::runtime_error("Failed to begin recording command buffer."); }

		VkClearValue clearColor { 0.0f, 0.0f, 0.0f, 1.0f };

		VkRenderPassBeginInfo renderPassInfo {};
		renderPassInfo.sType             = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass        = RenderPass::Get();
		renderPassInfo.framebuffer       = Framebuffers::Get()[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = SwapChain::GetExtent();
		renderPassInfo.clearValueCount   = 1;
		renderPassInfo.pClearValues      = &clearColor;

		vkCmdBeginRenderPass(s_CommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(s_CommandBuffers[i],
						  VK_PIPELINE_BIND_POINT_GRAPHICS,
						  GraphicsPipeline::Get());

		vkCmdDraw(s_CommandBuffers[i], 3, 1, 0, 0);

		vkCmdEndRenderPass(s_CommandBuffers[i]);

		VkResult recordResult = vkEndCommandBuffer(s_CommandBuffers[i]);
		if (recordResult != VK_SUCCESS)
		{ throw std::runtime_error("Failed to end recording command buffer"); }
	}
}

/*-----------------------------------------------------------------------------------------------*/
