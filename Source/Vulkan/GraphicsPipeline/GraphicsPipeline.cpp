#include "GraphicsPipeline.hpp"

VkPipeline       s_Pipeline;
VkPipelineLayout s_PipelineLayout;

/*------------------------------------------------------------------------------------------------*/
VkPipeline Vulkan::GraphicsPipeline::Get() { return s_Pipeline; }

/*------------------------------------------------------------------------------------------------*/
VkPipelineLayout Vulkan::GraphicsPipeline::GetLayout() { return s_PipelineLayout; }

/*------------------------------------------------------------------------------------------------*/
void Vulkan::GraphicsPipeline::Destroy()
{
	vkDestroyPipeline(Device::Logical::Get(), s_Pipeline, nullptr);
	vkDestroyPipelineLayout(Device::Logical::Get(), s_PipelineLayout, nullptr);
}

/*------------------------------------------------------------------------------------------------*/
void Vulkan::GraphicsPipeline::Create()
{
	auto vertShaderSource = Vulkan::Shader::ReadFile("../Assets/Shaders/vert.spv");
	auto fragShaderSource = Vulkan::Shader::ReadFile("../Assets/Shaders/frag.spv");

	VkShaderModule vertShaderModule = Vulkan::Shader::CreateShader(vertShaderSource);
	VkShaderModule fragShaderModule = Vulkan::Shader::CreateShader(fragShaderSource);

	VkPipelineShaderStageCreateInfo vertShaderStageCreateInfo {};
	vertShaderStageCreateInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageCreateInfo.stage  = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageCreateInfo.module = vertShaderModule;
	vertShaderStageCreateInfo.pName  = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageCreateInfo {};
	fragShaderStageCreateInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageCreateInfo.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageCreateInfo.module = fragShaderModule;
	fragShaderStageCreateInfo.pName  = "main";

	VkPipelineShaderStageCreateInfo shaderStages[2] = { vertShaderStageCreateInfo,
														fragShaderStageCreateInfo };

	VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo {};
	vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputStateCreateInfo.vertexBindingDescriptionCount   = 0;
	vertexInputStateCreateInfo.vertexAttributeDescriptionCount = 0;

	VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo {};
	inputAssemblyStateCreateInfo.sType =
		VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyStateCreateInfo.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
	inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport {};
	viewport.x        = 0.0f;
	viewport.y        = 0.0f;
	viewport.width    = (float)SwapChain::GetExtent().width;
	viewport.height   = (float)SwapChain::GetExtent().height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor {};
	scissor.offset = { 0, 0 };
	scissor.extent = SwapChain::GetExtent();

	VkPipelineViewportStateCreateInfo viewportStateCreateInfo {};
	viewportStateCreateInfo.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportStateCreateInfo.viewportCount = 1;
	viewportStateCreateInfo.pViewports    = &viewport;
	viewportStateCreateInfo.scissorCount  = 1;
	viewportStateCreateInfo.pScissors     = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo {};
	rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizationStateCreateInfo.depthClampEnable        = VK_FALSE;
	rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
	rasterizationStateCreateInfo.polygonMode             = VK_POLYGON_MODE_FILL;
	rasterizationStateCreateInfo.cullMode                = VK_CULL_MODE_BACK_BIT;
	rasterizationStateCreateInfo.frontFace               = VK_FRONT_FACE_CLOCKWISE;
	rasterizationStateCreateInfo.depthBiasEnable         = VK_FALSE;
	rasterizationStateCreateInfo.lineWidth               = 1.0f;
	rasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
	rasterizationStateCreateInfo.depthBiasClamp          = 0.0f;
	rasterizationStateCreateInfo.depthBiasSlopeFactor    = 0.0f;

	VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo {};
	multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampleStateCreateInfo.sampleShadingEnable   = VK_FALSE;
	multisampleStateCreateInfo.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
	multisampleStateCreateInfo.minSampleShading      = 1.0f;
	multisampleStateCreateInfo.pSampleMask           = nullptr;
	multisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
	multisampleStateCreateInfo.alphaToOneEnable      = VK_FALSE;

	VkPipelineColorBlendAttachmentState colorBlendAttachmentState {};
	colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
											   | VK_COLOR_COMPONENT_B_BIT
											   | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachmentState.blendEnable         = VK_FALSE;
	colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachmentState.colorBlendOp        = VK_BLEND_OP_ADD;
	colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachmentState.alphaBlendOp        = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo {};
	colorBlendStateCreateInfo.sType   = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
	colorBlendStateCreateInfo.logicOpEnable     = VK_FALSE;
	colorBlendStateCreateInfo.attachmentCount   = 1;
	colorBlendStateCreateInfo.pAttachments      = &colorBlendAttachmentState;
	colorBlendStateCreateInfo.blendConstants[0] = 0.0f;
	colorBlendStateCreateInfo.blendConstants[1] = 0.0f;
	colorBlendStateCreateInfo.blendConstants[2] = 0.0f;
	colorBlendStateCreateInfo.blendConstants[3] = 0.0f;

	// VkDynamicState dynamicStates[] = {
	// 	VK_DYNAMIC_STATE_VIEWPORT,
	// 	VK_DYNAMIC_STATE_LINE_WIDTH,
	// };

	// VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo {};
	// dynamicStateCreateInfo.sType             =
	// VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	// dynamicStateCreateInfo.dynamicStateCount = 2;
	// dynamicStateCreateInfo.pDynamicStates    = dynamicStates;

	VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo {};
	pipelineLayoutCreateInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutCreateInfo.setLayoutCount         = 0;
	pipelineLayoutCreateInfo.pSetLayouts            = nullptr;
	pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
	pipelineLayoutCreateInfo.pPushConstantRanges    = nullptr;

	VkResult resultPipelineLayout = vkCreatePipelineLayout(Device::Logical::Get(),
														   &pipelineLayoutCreateInfo,
														   nullptr,
														   &s_PipelineLayout);
	if (resultPipelineLayout != VK_SUCCESS)
	{ throw std::runtime_error("Failed to create the pipeline layout"); }

	VkGraphicsPipelineCreateInfo pipelineCreateInfo {};
	pipelineCreateInfo.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineCreateInfo.stageCount          = 2;
	pipelineCreateInfo.pStages             = shaderStages;
	pipelineCreateInfo.pVertexInputState   = &vertexInputStateCreateInfo;
	pipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
	pipelineCreateInfo.pViewportState      = &viewportStateCreateInfo;
	pipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
	pipelineCreateInfo.pMultisampleState   = &multisampleStateCreateInfo;
	pipelineCreateInfo.pDepthStencilState  = nullptr;
	pipelineCreateInfo.pColorBlendState    = &colorBlendStateCreateInfo;
	// pipelineCreateInfo.pDynamicState       = &dynamicStateCreateInfo;
	// pipelineCreateInfo.pDynamicState      = nullptr;  // For dynamic state comment this out.
	pipelineCreateInfo.layout             = s_PipelineLayout;
	pipelineCreateInfo.renderPass         = Vulkan::RenderPass::Get();
	pipelineCreateInfo.subpass            = 0;
	pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineCreateInfo.basePipelineIndex  = -1;

	VkResult result = vkCreateGraphicsPipelines(Device::Logical::Get(),
												VK_NULL_HANDLE,
												1,
												&pipelineCreateInfo,
												nullptr,
												&s_Pipeline);
	if (result != VK_SUCCESS) { throw std::runtime_error("Failed to create graphics pipeline."); }

	vkDestroyShaderModule(Device::Logical::Get(), vertShaderModule, nullptr);
	vkDestroyShaderModule(Device::Logical::Get(), fragShaderModule, nullptr);
}

/*------------------------------------------------------------------------------------------------*/
