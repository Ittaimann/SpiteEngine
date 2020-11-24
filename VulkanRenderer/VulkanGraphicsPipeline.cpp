#include "VulkanGraphicsPipeline.h"

VulkanGraphicsPipeline::VulkanGraphicsPipeline()
{
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
{
    cleanup();
}

void VulkanGraphicsPipeline::init(VkDevice device)
{
    mDevice = device;

    VkPipelineShaderStageCreateInfo shaderStages = createShaderStageInfo();
    VkPipelineVertexInputStateCreateInfo vertexState = createVertexInputStateInfo();
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyState = createInputAssemblyStateInfo();
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
    pipelineInfo.pViewportState = nullptr;
    pipelineInfo.pRasterizationState = nullptr;
    pipelineInfo.pMultisampleState = nullptr;
    pipelineInfo.pDepthStencilState = nullptr;
    pipelineInfo.pColorBlendState = nullptr;
    pipelineInfo.pDynamicState = nullptr;
    pipelineInfo.layout = nullptr;
    pipelineInfo.renderPass = nullptr;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = nullptr;
    pipelineInfo.basePipelineIndex = 0;
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
}