#ifndef VULKAN_DEVICE_H
#define VULKAN_DEVICE_H

#include "VulkanHelpers.h"

class VulkanDevice
{
public:
    VulkanDevice(/* args */);
    ~VulkanDevice();
    void init(bool enableValidation,VkPhysicalDevice physicalDevice,VulkanHelper::QueueFamilyIndices indices);
    void cleanup();

    VkDevice getDevice();
private:
    VkDevice mDevice;
    /* data */
};

#endif