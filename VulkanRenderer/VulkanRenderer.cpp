#include "VulkanRenderer.h"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
#include "WindowManager.h"

#include "VulkanVertexBuffer.h"
#include "VulkanRenderPass.h"
#include "VulkanFramebuffer.h"

VulkanRenderer::VulkanRenderer()
{
}
VulkanRenderer::~VulkanRenderer()
{
}

void VulkanRenderer::init(bool validation, WindowManager *window)
{
    mInstance.init(validation);
    mSurface.init(mInstance.getInstance(), window->getWindow());
    mPhysicalDevice.init(mInstance.getInstance(), mSurface.getVulkanSurface());
    VulkanHelper::QueueFamilyIndices queueFamilies = mPhysicalDevice.getFamilyIndices();
    mDevice.init(validation, mPhysicalDevice.getPhysicalDevice(), queueFamilies);
    mPresentQueue.init(mDevice.getDevice(), queueFamilies.presentFamily.value());
    mGraphicsQueue.init(mDevice.getDevice(), queueFamilies.graphicsFamily.value());
    mCommandPool.init(mDevice.getDevice(), queueFamilies.graphicsFamily.value());
    mSwapChain.init(mDevice.getDevice(), mSurface.getVulkanSurface(), mPhysicalDevice.getSwapChainDetails(), queueFamilies, window->getWidth(), window->getHeight());

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

void VulkanRenderer::buildModel(ModelLoad *model)
{
    VulkanVertexBuffer vertexBuffer;
    vertexBuffer.init(model, &mAllocator);
}

//TODO: expand this drastically, this will probably be a large amount of the texture builds
void VulkanRenderer::buildImage(VulkanImage& image,uint32_t width, uint32_t height, VkFormat format, VkImageUsageFlagBits usage, VkImageAspectFlags imageViewAspect)
{
    image.init(&mAllocator, mDevice.getDevice(), width, height, format, usage, imageViewAspect);
}

void VulkanRenderer::buildRenderPass(VulkanRenderPass &renderpass)
{
    renderpass.init(mDevice.getDevice());
}

VulkanFramebuffer VulkanRenderer::buildFramebuffer(uint32_t width, uint32_t height, const VulkanRenderPass &renderpass,const VulkanImage& bufferAttach /*,const std::vector<VkImageView>& imageViews*/)
{
    VulkanFramebuffer framebuffer;
    std::vector<VkImageView> imageViews = {mSwapChain.getImageView(0), bufferAttach.getImageView()};
    framebuffer.init(mDevice.getDevice(), width, height, renderpass, imageViews);
    return framebuffer;
}