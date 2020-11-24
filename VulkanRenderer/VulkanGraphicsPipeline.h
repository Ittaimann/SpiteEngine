#ifndef VULKAN_GRAPHICS_PIPELINE_H
#define VULKAN_GRAPHICS_PIPELINE_H

#include <vulkan/vulkan.h>
class VulkanGraphicsPipeline
{
public:
    VulkanGraphicsPipeline();
    ~VulkanGraphicsPipeline();
    void init(VkDevice device);
    void cleanup();
private:
    VkPipelineShaderStageCreateInfo createShaderStageInfo();
    VkPipelineVertexInputStateCreateInfo createVertexInputStateInfo();
    VkPipelineInputAssemblyStateCreateInfo createInputAssemblyStateInfo();

    VkPipeline mPipeline;
    VkDevice mDevice;
};

#endif