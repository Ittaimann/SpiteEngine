#include "VulkanGraphicsPipeline.h"

VulkanGraphicsPipeline::VulkanGraphicsPipeline()
{
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
{
    cleanup();
}

void VulkanGraphicsPipeline::init(VkDevice device, VkRenderPass renderpass)
{
    mDevice = device;

    VkPipelineShaderStageCreateInfo shaderStages = createShaderStageInfo();
    VkPipelineVertexInputStateCreateInfo vertexState = createVertexInputStateInfo();
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyState = createInputAssemblyStateInfo();

    VkViewport viewport = {0, 0, 480, 320, 1, 1};
    VkExtent2D extent = {480, 320};
    VkOffset2D offset = {0, 0};
    VkRect2D scissor = {offset, extent};
    VkPipelineViewportStateCreateInfo viewportState = createViewportStateInfo(viewport, scissor);
    VkPipelineRasterizationStateCreateInfo rasterizationState = createRasterizationStateInfo();
    VkPipelineMultisampleStateCreateInfo multiSampleState = createMultiSampleStateInfo();
    VkPipelineDepthStencilStateCreateInfo depthStencilState = createDepthStencilStateInfo();
    VkPipelineColorBlendStateCreateInfo colorBlendState = createColorBlendStateInfo();
    VkGraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.pNext = nullptr;
    pipelineInfo.flags = 0;
    pipelineInfo.stageCount = 1;          // hard coded for vertex stuff
    pipelineInfo.pStages = &shaderStages; // TODO: ACTUALLY MAKE SHADER UNITS
    pipelineInfo.pVertexInputState = &vertexState;
    pipelineInfo.pInputAssemblyState = &inputAssemblyState;
    pipelineInfo.pTessellationState = nullptr;
    //TODO: everything below this point.
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizationState;
    pipelineInfo.pMultisampleState = &multiSampleState;
    pipelineInfo.pDepthStencilState = &depthStencilState;
    pipelineInfo.pColorBlendState = &colorBlendState;
    pipelineInfo.pDynamicState = NULL;
    pipelineInfo.layout = nullptr;
    pipelineInfo.renderPass = renderpass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = nullptr;
    pipelineInfo.basePipelineIndex = 0;

    vkCreateGraphicsPipelines(device, nullptr, 1, &pipelineInfo, nullptr, &mPipeline);
}

void VulkanGraphicsPipeline::cleanup()
{
    vkDestroyPipeline(mDevice, mPipeline, nullptr);
}

VkPipelineShaderStageCreateInfo VulkanGraphicsPipeline::createShaderStageInfo()
{
    VkPipelineShaderStageCreateInfo pipelineShaderStageInfo = {};
    pipelineShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    pipelineShaderStageInfo.pNext = nullptr;
    pipelineShaderStageInfo.flags = 0;
    pipelineShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    pipelineShaderStageInfo.module = VK_NULL_HANDLE;
    pipelineShaderStageInfo.pName = "Uh... shader mc shader face";
    pipelineShaderStageInfo.pSpecializationInfo = nullptr;
    return pipelineShaderStageInfo;
}

VkPipelineVertexInputStateCreateInfo VulkanGraphicsPipeline::createVertexInputStateInfo()
{
    //TODO: move this to model creation and store in model? This also will be deallocated as part of this stack
    // move this out or something pls;
    VkVertexInputBindingDescription vertexInputBindingInfo = {}; // vertex buffer info
    vertexInputBindingInfo.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    vertexInputBindingInfo.binding = 0; //ooofers
    vertexInputBindingInfo.stride = 4;  //TODO: this is wrong;

    VkVertexInputAttributeDescription vertexInputAttributeInfo = {}; // vertice info
    vertexInputAttributeInfo.location = 0;
    vertexInputAttributeInfo.binding = 0;
    vertexInputAttributeInfo.format = VK_FORMAT_R32G32B32_SFLOAT;
    vertexInputAttributeInfo.offset = 0;

    VkPipelineVertexInputStateCreateInfo vertexInputStateInfo = {};
    vertexInputStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateInfo.pNext = nullptr;
    vertexInputStateInfo.flags = 0;
    vertexInputStateInfo.vertexBindingDescriptionCount = 1;
    vertexInputStateInfo.pVertexBindingDescriptions = &vertexInputBindingInfo;
    vertexInputStateInfo.vertexAttributeDescriptionCount = 1;
    vertexInputStateInfo.pVertexAttributeDescriptions = &vertexInputAttributeInfo;
    return vertexInputStateInfo;
}

VkPipelineInputAssemblyStateCreateInfo VulkanGraphicsPipeline::createInputAssemblyStateInfo()
{
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateInfo = {};
    inputAssemblyStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateInfo.pNext = nullptr;
    inputAssemblyStateInfo.flags = 0;
    inputAssemblyStateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssemblyStateInfo.primitiveRestartEnable = VK_FALSE; //Knowledge: da fuq is this
    return inputAssemblyStateInfo;
}

VkPipelineViewportStateCreateInfo VulkanGraphicsPipeline::createViewportStateInfo(const VkViewport &viewport, const VkRect2D &scissor)
{
    VkPipelineViewportStateCreateInfo viewportStateInfo = {};
    viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateInfo.pNext = nullptr;
    viewportStateInfo.flags = 0;
    viewportStateInfo.viewportCount = 1;
    viewportStateInfo.pViewports = &viewport;
    viewportStateInfo.scissorCount = 1;
    viewportStateInfo.pScissors = &scissor;

    return viewportStateInfo;
}

VkPipelineRasterizationStateCreateInfo VulkanGraphicsPipeline::createRasterizationStateInfo()
{
    VkPipelineRasterizationStateCreateInfo rasterizationStateInfo = {}; //Knowledge: refresh on some of these
    rasterizationStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateInfo.pNext = nullptr;
    rasterizationStateInfo.flags = 0;
    rasterizationStateInfo.depthClampEnable = VK_FALSE;
    rasterizationStateInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizationStateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationStateInfo.cullMode = VK_CULL_MODE_NONE; // TODO: set this properly
    rasterizationStateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizationStateInfo.depthBiasEnable = VK_FALSE;
    rasterizationStateInfo.depthBiasConstantFactor = 0;
    rasterizationStateInfo.depthBiasClamp = 0;
    rasterizationStateInfo.depthBiasSlopeFactor = 0;
    rasterizationStateInfo.lineWidth = 1;
    return rasterizationStateInfo;
}

VkPipelineMultisampleStateCreateInfo VulkanGraphicsPipeline::createMultiSampleStateInfo()
{

    VkPipelineMultisampleStateCreateInfo multisampleStateInfo = {};
    multisampleStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateInfo.pNext = nullptr;
    multisampleStateInfo.flags = 0;
    multisampleStateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampleStateInfo.sampleShadingEnable = VK_FALSE;
    multisampleStateInfo.minSampleShading = 0.0f;
    multisampleStateInfo.pSampleMask = nullptr;
    multisampleStateInfo.alphaToCoverageEnable = VK_FALSE;
    multisampleStateInfo.alphaToOneEnable = VK_FALSE;
    return multisampleStateInfo;
}

VkPipelineDepthStencilStateCreateInfo VulkanGraphicsPipeline::createDepthStencilStateInfo()
{
    //TODO: readjust these operations to actually cull reasonably
    VkStencilOpState stencilState = {};
    stencilState.failOp = VK_STENCIL_OP_KEEP;
    stencilState.passOp = VK_STENCIL_OP_KEEP;
    stencilState.depthFailOp = VK_STENCIL_OP_KEEP;
    stencilState.compareOp = VK_COMPARE_OP_ALWAYS;
    stencilState.compareMask = 0;
    stencilState.writeMask = 0;
    stencilState.reference = 0;

    VkPipelineDepthStencilStateCreateInfo depthStencilStateInfo = {};
    depthStencilStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilStateInfo.pNext = nullptr;
    depthStencilStateInfo.flags = 0;
    depthStencilStateInfo.depthTestEnable = VK_FALSE;
    depthStencilStateInfo.depthWriteEnable = VK_TRUE;
    depthStencilStateInfo.depthBoundsTestEnable = VK_FALSE;
    depthStencilStateInfo.depthCompareOp = VK_COMPARE_OP_ALWAYS;
    depthStencilStateInfo.stencilTestEnable = VK_FALSE;
    depthStencilStateInfo.front = stencilState;
    depthStencilStateInfo.back = stencilState;
    depthStencilStateInfo.minDepthBounds = 0;
    depthStencilStateInfo.maxDepthBounds = 1;
    return depthStencilStateInfo;
}

VkPipelineColorBlendStateCreateInfo VulkanGraphicsPipeline::createColorBlendStateInfo()
{
    VkPipelineColorBlendStateCreateInfo blendStateInfo = {};
    blendStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blendStateInfo.pNext = nullptr;
    blendStateInfo.flags = 0;
    blendStateInfo.logicOpEnable = VK_FALSE;
    blendStateInfo.logicOp = VK_LOGIC_OP_AND;
    blendStateInfo.attachmentCount = 2;
    blendStateInfo.pAttachments = nullptr; // OH FUCK REALLY?

    blendStateInfo.blendConstants[0] = 1.0f;
    blendStateInfo.blendConstants[1] = 1.0f;
    blendStateInfo.blendConstants[2] = 1.0f;
    blendStateInfo.blendConstants[3] = 1.0f;
    return blendStateInfo;
}
