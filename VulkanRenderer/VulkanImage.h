#ifndef VULKAN_IMAGE_H
#define VULKAN_IMAGE_H

#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

class VulkanImage{
public:
    VulkanImage();
    ~VulkanImage();
    void init(VmaAllocator allocator);
    void cleanup();
private:
    VkImage mImage;
    VmaAllocation mVmaAlloc;
    VmaAllocator* mAllocator;
};


#endif