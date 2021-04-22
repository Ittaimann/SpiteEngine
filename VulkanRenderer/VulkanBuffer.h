#ifndef VULKAN_BUFFER_H
#define VULKAN_BUFFER_H

#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

class VulkanBuffer
{
public:
    VulkanBuffer();
    ~VulkanBuffer();
    void init(VmaAllocator* allocator, void *data, uint32_t size, VkBufferUsageFlags usage, VmaMemoryUsage VmaUsage);
    void cleanup();
    

    VkBuffer getBuffer();
    void unstageBuffer(VkCommandBuffer commandBuffer, VulkanBuffer& src);
    void writeToBuffer(void* data, size_t size);

private:
    VmaAllocation mVmaAlloc;
    VmaAllocator* mAllocator;
    VkBuffer mBuffer;
    uint32_t mSize;
};

#endif
