#ifndef VULKAN_GRAPHICS_PIPELINE_H
#define VULKAN_GRAPHICS_PIPELINE_H

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanShader.h"

class VulkanGraphicsPipeline
{
public:
    VulkanGraphicsPipeline();
    ~VulkanGraphicsPipeline();
    void init(VkDevice device, VkRenderPass renderpass, const std::vector<VulkanShader> &shaders,VkDescriptorSetLayout descriptorSetLayout);
    void cleanup();
    VkPipeline getGraphicsPipeline();
    VkPipelineLayout getGraphicsPipelineLayout();
private:
    std::vector<VkPipelineShaderStageCreateInfo> createShaderStageInfo(const std::vector<VulkanShader> &shaders);
    VkPipelineVertexInputStateCreateInfo createVertexInputStateInfo(VkVertexInputBindingDescription &vertexInputBindingInfo, VkVertexInputAttributeDescription &vertexInputAttributeInfo);
    VkPipelineInputAssemblyStateCreateInfo createInputAssemblyStateInfo();
    VkPipelineViewportStateCreateInfo createViewportStateInfo(const VkViewport &viewport, const VkRect2D &scissor);
    VkPipelineRasterizationStateCreateInfo createRasterizationStateInfo();
    VkPipelineMultisampleStateCreateInfo createMultiSampleStateInfo();
    VkPipelineDepthStencilStateCreateInfo createDepthStencilStateInfo();
    VkPipelineColorBlendStateCreateInfo createColorBlendStateInfo(const std::vector<VkPipelineColorBlendAttachmentState> &blendAttachments);

    VkPipeline mPipeline;
    VkDevice mDevice;
    VkPipelineLayout mPipelineLayout;
};

#endif
