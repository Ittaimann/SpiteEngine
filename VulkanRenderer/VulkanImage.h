#ifndef VULKAN_IMAGE_H
#define VULKAN_IMAGE_H

#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

class VulkanImage{
public:
    VulkanImage();
    ~VulkanImage();
    void init(const VmaAllocator* allocator, VkDevice device, uint32_t width, uint32_t height, 
                VkFormat format, VkImageUsageFlagBits usage, VkImageAspectFlags imageViewAspect);
    void cleanup();
    VkImageView getImageView() const;
private:
    VkImage mImage;
    VkImageView mImageView; //TODO: reconsider this here. it is possible to have 1 image with multiple views
    VmaAllocation mVmaAlloc;
    const VmaAllocator* mAllocator;
    VkDevice mDevice;
};


#endif