#ifndef VULKAN_DRIVER_H
#define VULKAN_DRIVER_H

#include "VulkanHelpers.h"
#include "VulkanInstance.h"
#include "VulkanDevice.h"
#include "VulkanQueue.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanCommandPool.h"
#include "VulkanSurface.h"


class VulkanDriver
{
public:
    VulkanDriver(/* args */);
    ~VulkanDriver();

    void init();
    void cleanup();
private:

    //DRIVER INIT
    //TODO: refactor this though probably fine 
    VulkanInstance mInstance;
    VulkanDevice mDevice;
    VulkanQueue mPresentQueue;
    VulkanQueue mGraphicsQueue;
    VulkanPhysicalDevice mPhysicalDevice;
    VulkanSurface mSurface;
    VulkanCommandPool mCommandPool;
    /* data */
};


#endif // vulkan driver