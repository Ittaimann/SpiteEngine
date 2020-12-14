#define GLFW_INCLUDE_VULKAN //uh maybe a different place?
#include "VulkanRenderer.h"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
#include "Core/WindowManager.h"
#include "Core/ShaderLoad.h"

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

void VulkanRenderer::buildModel(VulkanVertexBuffer &vertexBuffer, ModelLoad *model)
{
    vertexBuffer.init(model, &mAllocator);
}

//TODO: expand this drastically, this will probably be a large amount of the texture builds
void VulkanRenderer::buildImage(VulkanImage &image, uint32_t width, uint32_t height, VkFormat format, VkImageUsageFlagBits usage, VkImageAspectFlags imageViewAspect)
{
    image.init(&mAllocator, mDevice.getDevice(), width, height, format, usage, imageViewAspect);
}

void VulkanRenderer::buildRenderPass(VulkanRenderPass &renderpass)
{
    renderpass.init(mDevice.getDevice());
}

void VulkanRenderer::buildFramebuffer(VulkanFramebuffer &framebuffer, uint32_t width, uint32_t height, const VulkanRenderPass &renderpass, const VulkanImage &bufferAttach /*,const std::vector<VkImageView>& imageViews*/)
{
    std::vector<VkImageView> imageViews = {mSwapChain.getImageView(0), bufferAttach.getImageView()};
    framebuffer.init(mDevice.getDevice(), width, height, renderpass, imageViews);
}

void VulkanRenderer::buildPipeline(VulkanGraphicsPipeline &pipeline, const VulkanRenderPass &renderpass, const std::vector<VulkanShader> &shaders)
{
    pipeline.init(mDevice.getDevice(), renderpass.getRenderPass(), shaders);
}

void VulkanRenderer::buildShader(VulkanShader &shader, ShaderLoad *shaderText)
{
    shader.init(mDevice.getDevice(), shaderText->getSize(), shaderText->getData());
}

//TODO: these imply only one command buffer, thats not how this is going to go.
// we will probably want a command buffer abstract that has its own begins and ends.
// request a command buffer struct that is stored inside of the commmandpool class that
// has all the needed extras (fences and semaphores?)
void VulkanRenderer::beginFrame()
{
    VkCommandBufferBeginInfo commandBufferBeginInfo = {};
    commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBufferBeginInfo.pNext = nullptr;
    commandBufferBeginInfo.pInheritanceInfo = nullptr;
    commandBufferBeginInfo.flags = 0;
    vkBeginCommandBuffer(mCommandPool.getCommandBuffer(), &commandBufferBeginInfo);
}
void VulkanRenderer::endFrame()
{
    vkEndCommandBuffer(mCommandPool.getCommandBuffer());
}

//TODO: tight renderpass and framebuffer together
void VulkanRenderer::beginRenderPass(VulkanRenderPass &renderpass, VulkanFramebuffer &framebuffer)
{
    VkRenderPassBeginInfo renderPassBeginInfo = {};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.pNext = nullptr;
    renderPassBeginInfo.renderPass = renderpass.getRenderPass();
    renderPassBeginInfo.framebuffer = framebuffer.getFramebuffer();
    renderPassBeginInfo.renderArea = framebuffer.getRenderArea(); //this could probably be set here instead of from the framebuffer but do that later
    renderPassBeginInfo.clearValueCount = 2;                      //TODO: temporary for one color and one depth attach;
    VkClearValue clears[2];
    renderPassBeginInfo.pClearValues = clears;

    vkCmdBeginRenderPass(mCommandPool.getCommandBuffer(), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanRenderer::endRenderPass()
{
    vkCmdEndRenderPass(mCommandPool.getCommandBuffer());
}

void VulkanRenderer::bindVertexBuffer(VulkanVertexBuffer &vertexBuffer)
{
    VkDeviceSize offsets = 0;
    VkBuffer baseBuffer = vertexBuffer.getBuffer();
    vkCmdBindVertexBuffers(mCommandPool.getCommandBuffer(), 0, 1, &baseBuffer, &offsets);
}

void VulkanRenderer::draw()
{
    vkCmdDraw(mCommandPool.getCommandBuffer(), 3, 1, 0, 0);
}

void VulkanRenderer::bindPipeline(VulkanGraphicsPipeline &pipeline)
{
    vkCmdBindPipeline(mCommandPool.getCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getGraphicsPipeline());
}


void VulkanRenderer::startNewFrame()
{
    mSwapChain.acquireImageIndex(mDevice.getDevice());
}

void VulkanRenderer::submitFrame()
{
    VkCommandBuffer submisionBuffer = mCommandPool.getCommandBuffer();
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = nullptr;
    submitInfo.waitSemaphoreCount = 0;
    submitInfo.pWaitSemaphores = nullptr;
    submitInfo.pWaitDstStageMask = nullptr;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &submisionBuffer;
    submitInfo.signalSemaphoreCount = 0;
    submitInfo.pSignalSemaphores = nullptr;
    VkResult result = vkQueueSubmit(mGraphicsQueue.getQueue(),1,&submitInfo,VK_NULL_HANDLE);
    assert(result == VK_SUCCESS);
}

void VulkanRenderer::presentFrame()
{
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 0;
    presentInfo.pWaitSemaphores = nullptr;
    VkSwapchainKHR swapChains[] = {mSwapChain.getSwapChain()};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    uint32_t imageIndex = 0;
    presentInfo.pImageIndices = mSwapChain.getNextImageIndex();
    presentInfo.pResults = nullptr; // Optional
    vkQueuePresentKHR(mPresentQueue.getQueue(), &presentInfo);
    vkDeviceWaitIdle(mDevice.getDevice());


}