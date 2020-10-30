#ifndef VULKAN_BUFFER_H
#define VULKAN_BUFFER_H

#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

class VulkanBuffer
{
public:
    VulkanBuffer();
    ~VulkanBuffer();
    void init(VmaAllocator allocator, void* data, uint32_t size, VmaMemoryUsage usage);
    void cleanup(VmaAllocator allocator);

private:
    VkBuffer mBuffer;
    VmaAllocation mVmaAlloc;

    uint32_t mSize;
};

#endif