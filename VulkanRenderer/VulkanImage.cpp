#include "VulkanImage.h"
#include <assert.h>
VulkanImage::VulkanImage()
{
}

VulkanImage::~VulkanImage()
{
    cleanup();
}

void VulkanImage::init(const VmaAllocator* allocator, VkDevice device, uint32_t width, uint32_t height, 
                    VkFormat format, VkImageUsageFlagBits usage, VkImageAspectFlags imageViewAspect)
{
    mAllocator = allocator;
    mDevice = device;

    // TODO: this is importante, let this get set more granularly
    VkImageCreateInfo imageInfo = {};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.pNext = nullptr;
    imageInfo.flags = 0;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = format;
    imageInfo.extent = {width, height, 1}; // last one is depth
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT; //Knowledge: multi sample framebuffer? investigate
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.usage = usage;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; //Knowledge: what exactly is this for
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

    VkResult result = vmaCreateImage(*allocator, &imageInfo, &allocInfo, &mImage, &mVmaAlloc, nullptr);
    assert(result == VK_SUCCESS);

    VkImageViewCreateInfo imageViewInfo = {};
    imageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewInfo.pNext = nullptr;
    imageViewInfo.flags = 0;
    imageViewInfo.image = mImage;
    imageViewInfo.format = format;
    imageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D; // TODO: base this on image type in future
    imageViewInfo.components = {VK_COMPONENT_SWIZZLE_IDENTITY , VK_COMPONENT_SWIZZLE_IDENTITY , VK_COMPONENT_SWIZZLE_IDENTITY , VK_COMPONENT_SWIZZLE_IDENTITY };
    imageViewInfo.subresourceRange.aspectMask = imageViewAspect;
    imageViewInfo.subresourceRange.baseArrayLayer = 0;
    imageViewInfo.subresourceRange.baseMipLevel = 0;
    imageViewInfo.subresourceRange.layerCount = 1;
    imageViewInfo.subresourceRange.levelCount = 1;

    vkCreateImageView(device, &imageViewInfo,nullptr,&mImageView);
}

void VulkanImage::cleanup()
{
    vmaDestroyImage(*mAllocator, mImage, mVmaAlloc);
    vkDestroyImageView(mDevice,mImageView,nullptr);
}

VkImageView VulkanImage::getImageView() const
{
    return mImageView;
}

