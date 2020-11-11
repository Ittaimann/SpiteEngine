#include "VulkanRenderer.h"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
#include "WindowManager.h"

#include "VulkanVertexBuffer.h"
#include "VulkanRenderPass.h"


VulkanRenderer::VulkanRenderer()
{}
VulkanRenderer::~VulkanRenderer()
{}

void VulkanRenderer::init(bool validation, WindowManager *window)
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

void VulkanRenderer::cleanup()
{
    mCommandPool.cleanup(mDevice.getDevice());
    mSwapChain.cleanup(mDevice.getDevice());
    vmaDestroyAllocator(mAllocator);
    mDevice.cleanup();
    mSurface.cleanup(mInstance.getInstance());
    mInstance.cleanup();
}

void VulkanRenderer::buildModel(ModelLoad* model)
{
    VulkanVertexBuffer vertexBuffer;
    vertexBuffer.init(model,&mAllocator);
}

void VulkanRenderer::buildRenderPass()
{
    VulkanRenderPass renderPass;
    renderPass.init(mDevice.getDevice());
}
