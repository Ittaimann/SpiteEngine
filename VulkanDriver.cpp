#include "VulkanDriver.h"

VulkanDriver::VulkanDriver()
{}
VulkanDriver::~VulkanDriver()
{}

void VulkanDriver::init(bool validation, GLFWwindow *window)
{
    mInstance.init(validation);
    mSurface.init(mInstance.getVulkanInstance(), window);
    mPhysicalDevice.init(mInstance.getVulkanInstance(),mSurface.getVulkanSurface());
    VulkanHelper::QueueFamilyIndices queueFamilies = mPhysicalDevice.getFamilyIndices();
    mDevice.init(validation, mPhysicalDevice.getPhysicalDevice(),queueFamilies);
    mPresentQueue.init(mDevice.getDevice(),queueFamilies.presentFamily.value());
    mGraphicsQueue.init(mDevice.getDevice(),queueFamilies.graphicsFamily.value());
    mCommandPool.init(mDevice.getDevice(), queueFamilies.graphicsFamily.value());
}

void VulkanDriver::cleanup()
{
    mCommandPool.cleanup(mDevice.getDevice());
    mDevice.cleanup();
    mSurface.cleanup();
    mInstance.cleanup();
}


