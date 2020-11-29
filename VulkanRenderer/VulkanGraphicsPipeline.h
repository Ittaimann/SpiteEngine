#ifndef VULKAN_GRAPHICS_PIPELINE_H
#define VULKAN_GRAPHICS_PIPELINE_H

#include <vulkan/vulkan.h>
class VulkanGraphicsPipeline
{
public:
    VulkanGraphicsPipeline();
    ~VulkanGraphicsPipeline();
    void init(VkDevice device, VkRenderPass renderpass);
    void cleanup();

private:
    VkPipelineShaderStageCreateInfo createShaderStageInfo();
    VkPipelineVertexInputStateCreateInfo createVertexInputStateInfo();
    VkPipelineInputAssemblyStateCreateInfo createInputAssemblyStateInfo();
    VkPipelineViewportStateCreateInfo createViewportStateInfo(const VkViewport &viewport, const VkRect2D &scissor);
    VkPipelineRasterizationStateCreateInfo createRasterizationStateInfo();
    VkPipelineMultisampleStateCreateInfo createMultiSampleStateInfo();
    VkPipelineDepthStencilStateCreateInfo createDepthStencilStateInfo();
    VkPipelineColorBlendStateCreateInfo createColorBlendStateInfo();

    VkPipeline mPipeline;
    VkDevice mDevice;
};

#endif