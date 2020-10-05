#ifndef VULKAN_BUFFER_H
#define VULKAN_BUFFER_H

#include <vulkan/vulkan.h>

class VulkanBuffer
{
public:
    VulkanBuffer();
    ~VulkanBuffer();
    void init();
    void cleanup();

private:
    VkBuffer mBuffer;
};



#endif