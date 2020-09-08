#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H


//vulkan pch?
#include "VulkanHelpers.h"

class VulkanInstance
{
public:
    VulkanInstance(/* args */);
    ~VulkanInstance();
    void init();
    VkInstance getVulkanInstance();
private:
    VkInstance mInstance; // the instance
};

#endif