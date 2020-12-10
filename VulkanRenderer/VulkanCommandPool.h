#ifndef VULKAN_COMMAND_POOL_H
#define VULKAN_COMMAND_POOL_H

#include <vulkan/vulkan.h>

class VulkanCommandPool
{
public:
    VulkanCommandPool();
    ~VulkanCommandPool();
    void init(VkDevice device, uint32_t graphicsFamily);
    void cleanup(VkDevice device);

    VkCommandBuffer getCommandBuffer();
private:
    VkCommandPool mCommandPool;
    VkCommandBuffer mCommandBuffer; // TODO: do a proper pool of these. 
};

#endif