#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H


#include "VulkanHelpers.h"
#include "VulkanInstance.h"
#include "VulkanDevice.h"
#include "VulkanQueue.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanCommandPool.h"
#include "VulkanSurface.h"
#include "VulkanSwapChain.h"
#include "vk_mem_alloc.h" //TODO: figure out why this needs to be dupped in cpp and here, probably need a precompile header

class WindowManager;
class ModelLoad;

class VulkanRenderer
{
public:
    VulkanRenderer();
    ~VulkanRenderer();

    void init(bool validation,WindowManager* window);
    void cleanup();

    void buildModel(ModelLoad* model);
    void buildRenderPass();

private:

    VulkanInstance mInstance;
    VulkanDevice mDevice;
    VulkanQueue mPresentQueue;
    VulkanQueue mGraphicsQueue;
    VulkanPhysicalDevice mPhysicalDevice;
    VulkanSurface mSurface;
    VulkanCommandPool mCommandPool;
    VulkanSwapChain mSwapChain;
    VmaAllocator mAllocator;// optimize: maybe switch this to be a pointer and foward declare.
};


#endif // vulkan driver