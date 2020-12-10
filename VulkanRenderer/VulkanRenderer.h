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

#include "VulkanImage.h" // TODO: could probably foward declare this instead
#include "VulkanRenderPass.h"
#include "VulkanFramebuffer.h"
#include "VulkanRenderPass.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanShader.h"
#include "VulkanVertexBuffer.h"

class WindowManager;
class ModelLoad;
class ShaderLoad;

class VulkanRenderer
{
public:
    VulkanRenderer();
    ~VulkanRenderer();

    void init(bool validation, WindowManager *window);
    void cleanup();

    void buildModel(VulkanVertexBuffer& vertexBuffer, ModelLoad *model);
    void buildImage(VulkanImage &image, uint32_t width, uint32_t height, VkFormat format, VkImageUsageFlagBits usage, VkImageAspectFlags imageViewAspect);
    void buildRenderPass(VulkanRenderPass &renderpass);
    void buildFramebuffer(VulkanFramebuffer &framebuffer, uint32_t width, uint32_t height, const VulkanRenderPass &renderpass, const VulkanImage &bufferAttach /*,const std::vector<VkImageView>& imageViews*/);
    void buildPipeline(VulkanGraphicsPipeline& pipeline,const VulkanRenderPass& renderpass, const std::vector<VulkanShader>& shaders);
    void buildShader(VulkanShader& shader, ShaderLoad* shaderText);

    void beginFrame();
    void endFrame();
    void beginRenderPass(VulkanRenderPass &renderpass, VulkanFramebuffer &framebuffer);
    void endRenderPass();

    void draw();

    //TODO: const this down te whole at some point. this
    void bindVertexBuffer(VulkanVertexBuffer& vertexBuffer);
    void bindPipeline(VulkanGraphicsPipeline& pipeline);

private:
    VulkanInstance mInstance;
    VulkanDevice mDevice;
    VulkanQueue mPresentQueue;
    VulkanQueue mGraphicsQueue;
    VulkanPhysicalDevice mPhysicalDevice;
    VulkanSurface mSurface;
    VulkanCommandPool mCommandPool;
    VulkanSwapChain mSwapChain;
    VmaAllocator mAllocator; // optimize: maybe switch this to be a pointer and foward declare.
};

#endif // vulkan driver