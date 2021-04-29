#include "VulkanSwapChain.h"
#include <algorithm>

VulkanSwapChain::VulkanSwapChain()
{
}
VulkanSwapChain::~VulkanSwapChain()
{
}

void VulkanSwapChain::init(VkDevice device, VkSurfaceKHR surface, const VulkanHelper::SwapChainSupportDetails &swapChainSupport,
                           VulkanHelper::QueueFamilyIndices indices, uint32_t width, uint32_t height)
{

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, width, height);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily)
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &mSwapChain);
    assert(result == VK_SUCCESS);

    vkGetSwapchainImagesKHR(device, mSwapChain, &imageCount, nullptr);
    mSwapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device, mSwapChain, &imageCount, mSwapChainImages.data());

    mSwapChainImageFormat = surfaceFormat.format;
    mSwapChainExtent = extent;
    createImageViews(device);

    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.pNext = nullptr;
    semaphoreInfo.flags = 0;
    vkCreateSemaphore(device, &semaphoreInfo, nullptr, &mSwapChainSemaphore);
}

void VulkanSwapChain::cleanup(VkDevice device)
{
    for (size_t i = 0; i < mSwapChainImages.size(); i++)
    {
        vkDestroyImageView(device, mSwapChainImageViews[i], nullptr);
    }
    vkDestroySemaphore(device, mSwapChainSemaphore, nullptr);

    vkDestroySwapchainKHR(device, mSwapChain, nullptr); //also clears the images
}

void VulkanSwapChain::createImageViews(VkDevice device)
{
    mSwapChainImageViews.resize(mSwapChainImages.size());
    for (size_t i = 0; i < mSwapChainImages.size(); i++)
    {
        VkImageViewCreateInfo imageViewInfo{};
        imageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewInfo.image = mSwapChainImages[i];
        imageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewInfo.format = mSwapChainImageFormat;
        imageViewInfo.components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY};
        imageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageViewInfo.subresourceRange.baseMipLevel = 0;
        imageViewInfo.subresourceRange.levelCount = 1;
        imageViewInfo.subresourceRange.baseArrayLayer = 0;
        imageViewInfo.subresourceRange.layerCount = 1;

        VkResult result = vkCreateImageView(device, &imageViewInfo, nullptr, &mSwapChainImageViews[i]);
        assert(result == VK_SUCCESS);
    }
}

VkSwapchainKHR VulkanSwapChain::getSwapChain()
{
    return mSwapChain;
}

std::vector<VkImageView> VulkanSwapChain::getImageViews()
{
    return mSwapChainImageViews;
}

std::vector<VkImage> VulkanSwapChain::getSwapChainImages()
{
    return mSwapChainImages;
}
VkFormat VulkanSwapChain::getSwapChainFormat()
{
    return mSwapChainImageFormat;
}
VkExtent2D VulkanSwapChain::getSwapChainExtent()
{
    return mSwapChainExtent;
}

VkSurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
    for (const auto &availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR VulkanSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
{
    for (const auto &availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}
VkExtent2D VulkanSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, uint32_t width, uint32_t height)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
    {
        return capabilities.currentExtent;
    }
    else
    {

        VkExtent2D actualExtent = {width, height};

        actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

void VulkanSwapChain::acquireImageIndex(VkDevice device)
{
    vkAcquireNextImageKHR(device, mSwapChain, UINT64_MAX, mSwapChainSemaphore, VK_NULL_HANDLE, &mImageIndex);
}

uint32_t *VulkanSwapChain::getNextImageIndex()
{
    return &mImageIndex;
}

VkSemaphore VulkanSwapChain::getSwapChainSemaphore()
{
    return mSwapChainSemaphore;
}
