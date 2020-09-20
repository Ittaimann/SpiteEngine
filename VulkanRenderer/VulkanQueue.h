#ifndef VULKAN_QUEUE_H
#define VULKAN_QUEUE_H

#include "VulkanHelpers.h"

class VulkanQueue
{
public:
    VulkanQueue(/* args */);
    ~VulkanQueue();
    void init(VkDevice device,uint32_t family);
    void cleanup();
private:
    VkQueue mQueue;
};

#endif