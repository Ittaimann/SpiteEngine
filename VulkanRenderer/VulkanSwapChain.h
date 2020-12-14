#ifndef VULKAN_SWAPCHAIN_H
#define VULKAN_SWAPCHAIN_H

#include "VulkanHelpers.h"
#include <vector>

class VulkanSwapChain
{
public:
    VulkanSwapChain();
    ~VulkanSwapChain();
    void init(VkDevice device, VkSurfaceKHR surface, const VulkanHelper::SwapChainSupportDetails &swapChainSupport,
              VulkanHelper::QueueFamilyIndices indices, uint32_t width, uint32_t height);
    void cleanup(VkDevice device);

    void createImageViews(VkDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, uint32_t width, uint32_t height);
    void acquireImageIndex(VkDevice device);
    VkSwapchainKHR getSwapChain();
    std::vector<VkImage> getSwapChainImages();
    VkImageView getImageView(uint32_t swapChainIndex);
    VkFormat getSwapChainFormat();
    VkExtent2D getSwapChainExtent();
    uint32_t* getNextImageIndex();
private:
    VkSwapchainKHR mSwapChain;
    std::vector<VkImage> mSwapChainImages;
    std::vector<VkImageView> mSwapChainImageViews;
    VkFormat mSwapChainImageFormat;
    VkExtent2D mSwapChainExtent;
    uint32_t imageIndex;
};

#endif