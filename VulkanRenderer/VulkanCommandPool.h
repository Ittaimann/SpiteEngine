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
    VkCommandBuffer getTransientCommandBuffer(VkDevice device);
private:
    VkCommandPool mCommandPool;
    VkCommandBuffer mCommandBuffer; // TODO: do a proper pool of these.
    VkCommandBuffer mTransientCommandBuffer; // TODO: do a proper pool of these.

    // todo: create a VkFence and maybe a semaphore per commandBuffer? 
};

#endif