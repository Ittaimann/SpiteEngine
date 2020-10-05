#ifndef VULKAN_PHYSICAL_DEVICE_H
#define VULKAN_PHYSICAL_DEVICE_H

#include "VulkanHelpers.h"

class VulkanPhysicalDevice
{
public:
    VulkanPhysicalDevice(/* args */);
    ~VulkanPhysicalDevice();
    void init(VkInstance instance, VkSurfaceKHR surface);
    void cleanup();

    VkPhysicalDevice getPhysicalDevice();
    VulkanHelper::QueueFamilyIndices getFamilyIndices();
    VulkanHelper::SwapChainSupportDetails getSwapChainDetails();
private:

    VkPhysicalDevice mPhysicalDevice;
    VulkanHelper::QueueFamilyIndices mQueueFamilies;
    VulkanHelper::SwapChainSupportDetails mSwapChainDetails;

    VulkanHelper::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    VulkanHelper::SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
    bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
    VkPhysicalDevice FindGraphicsDevice(VkInstance instance, VkSurfaceKHR surface);

};

#endif