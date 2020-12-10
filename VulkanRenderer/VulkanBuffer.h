#ifndef VULKAN_BUFFER_H
#define VULKAN_BUFFER_H

#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

class VulkanBuffer
{
public:
    VulkanBuffer();
    ~VulkanBuffer();
    void init(VmaAllocator allocator, void *data, uint32_t size, VkBufferUsageFlags usage, VmaMemoryUsage VmaUsage);
    void cleanup(VmaAllocator allocator);
    VkBuffer& getBuffer();
private:
    VkBuffer mBuffer;
    VmaAllocation mVmaAlloc;
    VmaAllocator* mAllocator;
    uint32_t mSize;
};

#endif