#ifndef VULKAN_COMMAND_POOL_H
#define VULKAN_COMMAND_POOL_H

#include "VulkanHelpers.h"

class VulkanCommandPool
{
public:
    VulkanCommandPool(/* args */);
    ~VulkanCommandPool();
    void init(VkDevice device, uint32_t graphicsFamily);
    void cleanup(VkDevice device);
private:
    VkCommandPool mCommandPool;
};

#endif