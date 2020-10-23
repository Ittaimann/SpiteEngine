#include "VulkanDriver.h"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
#include "WindowManager.h"



VulkanDriver::VulkanDriver()
{}
VulkanDriver::~VulkanDriver()
{}

void VulkanDriver::init(bool validation, WindowManager *window)
{
    mInstance.init(validation);
    mSurface.init(mInstance.getInstance(), window->getWindow());
    mPhysicalDevice.init(mInstance.getInstance(),mSurface.getVulkanSurface());
    VulkanHelper::QueueFamilyIndices queueFamilies = mPhysicalDevice.getFamilyIndices();
    mDevice.init(validation, mPhysicalDevice.getPhysicalDevice(),queueFamilies);
    mPresentQueue.init(mDevice.getDevice(),queueFamilies.presentFamily.value());
    mGraphicsQueue.init(mDevice.getDevice(),queueFamilies.graphicsFamily.value());
    mCommandPool.init(mDevice.getDevice(), queueFamilies.graphicsFamily.value());
    mSwapChain.init(mDevice.getDevice(),mSurface.getVulkanSurface(),mPhysicalDevice.getSwapChainDetails(),queueFamilies,window->getWidth(),window->getHeight());

    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.physicalDevice = mPhysicalDevice.getPhysicalDevice();
    allocatorInfo.device = mDevice.getDevice();
    allocatorInfo.instance = mInstance.getInstance();

    vmaCreateAllocator(&allocatorInfo, &mAllocator);

}

void VulkanDriver::cleanup()
{
    mCommandPool.cleanup(mDevice.getDevice());
    mSwapChain.cleanup(mDevice.getDevice());
    mDevice.cleanup();
    mSurface.cleanup(mInstance.getInstance());
    mInstance.cleanup();
}


