#include "VulkanGraphicsPipeline.h"

//TODO: move these glm defines out, these should NOT BE HERE
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

VulkanGraphicsPipeline::VulkanGraphicsPipeline()
{
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
{
    cleanup();
}

VkPipeline VulkanGraphicsPipeline::getGraphicsPipeline()
{
    return mPipeline;
}

void VulkanGraphicsPipeline::init(VkDevice device, VkRenderPass renderpass, const std::vector<VulkanShader> &shaders)
{
    mDevice = device;

    std::vector<VkPipelineShaderStageCreateInfo> shaderStages = createShaderStageInfo(shaders);

    VkVertexInputBindingDescription vertexInputBindingInfo = {}; // vertex buffer info
    vertexInputBindingInfo.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    vertexInputBindingInfo.binding = 0;                //ooofers
    vertexInputBindingInfo.stride = sizeof(glm::vec3); //TODO: this is wrong;

    VkVertexInputAttributeDescription vertexInputAttributeInfo = {}; // vertice info
    vertexInputAttributeInfo.location = 0;
    vertexInputAttributeInfo.binding = 0;
    vertexInputAttributeInfo.format = VK_FORMAT_R32G32B32_SFLOAT;
    vertexInputAttributeInfo.offset = 0;

    VkPipelineVertexInputStateCreateInfo vertexState = createVertexInputStateInfo(vertexInputBindingInfo, vertexInputAttributeInfo);
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyState = createInputAssemblyStateInfo();

    VkViewport viewport = {0, 0, 480, 320, 1, 1};
    VkExtent2D extent = {480, 320};
    VkOffset2D offset = {0, 0};
    VkRect2D scissor = {offset, extent};
    VkPipelineViewportStateCreateInfo viewportState = createViewportStateInfo(viewport, scissor);
    VkPipelineRasterizationStateCreateInfo rasterizationState = createRasterizationStateInfo();
    VkPipelineMultisampleStateCreateInfo multiSampleState = createMultiSampleStateInfo();
    VkPipelineDepthStencilStateCreateInfo depthStencilState = createDepthStencilStateInfo();

    //TODO: these blends will probably need to be controlled by my meta shader data. interesting its per attachment, might make it difficult. maybe need to make a rendergraph and have a dependency check
    std::vector<VkPipelineColorBlendAttachmentState> blendAttachments(1);
    for (int i = 0; i < blendAttachments.size(); i++)
    {
        blendAttachments[i].colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        blendAttachments[i].blendEnable = VK_FALSE;
        blendAttachments[i].srcColorBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
        blendAttachments[i].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        blendAttachments[i].colorBlendOp = VK_BLEND_OP_ADD;             // Optional
        blendAttachments[i].srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
        blendAttachments[i].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        blendAttachments[i].alphaBlendOp = VK_BLEND_OP_ADD;             // Optional
    }
    VkPipelineColorBlendStateCreateInfo colorBlendState = createColorBlendStateInfo(blendAttachments);

    VkGraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.pNext = nullptr;
    pipelineInfo.flags = 0;
    pipelineInfo.stageCount = shaderStages.size();
    pipelineInfo.pStages = shaderStages.data();
    pipelineInfo.pVertexInputState = &vertexState;
    pipelineInfo.pInputAssemblyState = &inputAssemblyState;
    pipelineInfo.pTessellationState = nullptr;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizationState;
    pipelineInfo.pMultisampleState = &multiSampleState;
    pipelineInfo.pDepthStencilState = &depthStencilState;
    pipelineInfo.pColorBlendState = &colorBlendState;
    pipelineInfo.pDynamicState = NULL;

    //TODO: REMOVE THIS SO WE CAN ACTUALLY LOAD UNIFORMS
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;            // Optional
    pipelineLayoutInfo.pSetLayouts = nullptr;         // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0;    // Optional
    pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional
    VkPipelineLayout lol;
    vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &lol);

    pipelineInfo.layout = lol;
    pipelineInfo.renderPass = renderpass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = nullptr;
    pipelineInfo.basePipelineIndex = 0;

    vkCreateGraphicsPipelines(device, nullptr, 1, &pipelineInfo, nullptr, &mPipeline);

    //TODO: REMOVE THIS NONSENSE
    vkDestroyPipelineLayout(device, lol, nullptr);
}

void VulkanGraphicsPipeline::cleanup()
{
    vkDestroyPipeline(mDevice, mPipeline, nullptr);
}

std::vector<VkPipelineShaderStageCreateInfo> VulkanGraphicsPipeline::createShaderStageInfo(const std::vector<VulkanShader> &shaders)
{
    std::vector<VkPipelineShaderStageCreateInfo> pipelineShaderStageInfo(shaders.size());
    for (int i = 0; i < shaders.size(); i++)
    {
        pipelineShaderStageInfo[i].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        pipelineShaderStageInfo[i].pNext = nullptr;
        pipelineShaderStageInfo[i].flags = 0;
        pipelineShaderStageInfo[i].module = shaders[i].getShaderModule();
        pipelineShaderStageInfo[i].pName = "main";
        pipelineShaderStageInfo[i].pSpecializationInfo = nullptr;
    }
    pipelineShaderStageInfo[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    pipelineShaderStageInfo[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;

    return pipelineShaderStageInfo;
}

//TODO: move this to model creation and store in some kind of map? no need to recreate this on the model every time. also one of these is not model specific (instance data)
VkPipelineVertexInputStateCreateInfo VulkanGraphicsPipeline::createVertexInputStateInfo(VkVertexInputBindingDescription &vertexInputBindingInfo, VkVertexInputAttributeDescription &vertexInputAttributeInfo)
{
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

VkPipelineColorBlendStateCreateInfo VulkanGraphicsPipeline::createColorBlendStateInfo(const std::vector<VkPipelineColorBlendAttachmentState> &blendAttachments)
{
    VkPipelineColorBlendStateCreateInfo blendStateInfo = {};
    blendStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blendStateInfo.pNext = nullptr;
    blendStateInfo.flags = 0;
    blendStateInfo.logicOpEnable = VK_FALSE;
    blendStateInfo.logicOp = VK_LOGIC_OP_AND;
    blendStateInfo.attachmentCount = 1;
    blendStateInfo.pAttachments = blendAttachments.data();

    blendStateInfo.blendConstants[0] = 1.0f;
    blendStateInfo.blendConstants[1] = 1.0f;
    blendStateInfo.blendConstants[2] = 1.0f;
    blendStateInfo.blendConstants[3] = 1.0f;
    return blendStateInfo;
}
