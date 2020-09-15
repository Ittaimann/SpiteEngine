#ifndef VULKAN_SWAPCHAIN_H
#define VULKAN_SWAPCHAIN_H

#include "VulkanHelpers.h"

class VulkanSwapChain
{
public:
    VulkanSwapChain();
    ~VulkanSwapChain();
    void init();
    void cleanup();
private:
    VkSwapchainKHR mSwapChain;
};

#endif