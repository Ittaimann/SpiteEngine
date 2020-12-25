#ifndef VULKAN_COMMAND_POOL_H
#define VULKAN_COMMAND_POOL_H

#include <vulkan/vulkan.h>
#include <vector>

class VulkanCommandPool
{
public:
    VulkanCommandPool();
    ~VulkanCommandPool();
    void init(VkDevice device, uint32_t graphicsFamily);
    void cleanup(VkDevice device);
    void endFrame();

    VkCommandBuffer allocateCommandBuffer();
    void beginRecording();
    void endRecording();

    VkCommandBuffer getCommandBuffer();
    std::vector<VkCommandBuffer> getUsedCommandBuffers();

private:
    VkCommandPool mCommandPool;
    VkDevice mDevice;
    std::vector<VkCommandBuffer> mFreeCommandBufferQueue;
    std::vector<VkCommandBuffer> mUsedCommandBufferQueue;
    VkCommandBuffer mCommandBuffer;
    //TODO: if we have stand alone submits we may want to add semaphores here
};

#endif