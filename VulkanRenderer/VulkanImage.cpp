#include "VulkanImage.h"
#include <assert.h>
VulkanImage::VulkanImage()
{
}

VulkanImage::~VulkanImage()
{
}

void VulkanImage::init(VmaAllocator allocator)
{
    mAllocator = &allocator;

    VkImageCreateInfo imageInfo = {};
    
    VmaAllocationCreateInfo allocInfo = {};

    VkResult result = vmaCreateImage(allocator, &imageInfo, &allocInfo, &mImage, &mVmaAlloc, nullptr);
}

void VulkanImage::cleanup()
{
}