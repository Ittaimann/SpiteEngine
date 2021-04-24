#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H
#include <functional>

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

    void buildModel(VulkanVertexBuffer& vertexBuffer, ModelLoad *model, bool deviceLocal);
    void buildImage(VulkanImage &image, uint32_t width, uint32_t height, VkFormat format, VkImageUsageFlagBits usage, VkImageAspectFlags imageViewAspect);
    void buildRenderPass(VulkanRenderPass &renderpass);
    void buildFramebuffer(VulkanFramebuffer &framebuffer, uint32_t width, uint32_t height, const VulkanRenderPass &renderpass, const VulkanImage &bufferAttach /*,const std::vector<VkImageView>& imageViews*/);
    void buildPipeline(VulkanGraphicsPipeline& pipeline,const VulkanRenderPass& renderpass, const std::vector<VulkanShader>& shaders);
    void buildShader(VulkanShader& shader, ShaderLoad* shaderText);
    void buildBuffer(VulkanBuffer& buffer, size_t size, VkBufferUsageFlags tempUsageFlag, void* data = nullptr);
    void buildDescriptorSet(uint32_t bufferDescNum, VulkanBuffer* vulkanBuffers); // TODO: add textures and other descriptors

    // TODO: rename these/repuprose these, change them to begin recording or something
    void beginFrame();
    void endFrame();
    void beginRecording();
    void endRecording();

    void beginRenderPass(VulkanRenderPass &renderpass, VulkanFramebuffer &framebuffer);
    void endRenderPass();

    void draw();
    void startNewFrame();
    void submitFrame();
    void presentFrame();
    
    //TODO: const this down te whole at some point. this
    void bindVertexBuffer(VulkanVertexBuffer& vertexBuffer);
    void bindPipeline(VulkanGraphicsPipeline& pipeline);

    VulkanFramebuffer* getFrontBuffer(); //return based on current frame
    VulkanRenderPass* getFrontRenderPass();

private:
    void initFrontBuffer();

    VulkanInstance mInstance;
    VulkanDevice mDevice;
    VulkanQueue mPresentQueue;
    VulkanQueue mGraphicsQueue;
    VulkanPhysicalDevice mPhysicalDevice;
    VulkanSurface mSurface;
    VulkanCommandPool mCommandPool;
    VulkanSwapChain mSwapChain;
    VmaAllocator mAllocator; // OPTIMIZE: maybe switch this to be a pointer and foward declare.
    VkDescriptorPool mDescriptorPool;
    VkSemaphore mQueueSubmitSemaphore;
    std::vector<VulkanFramebuffer> mFrontFrameBuffers; //TODO: replace this with a proper max frames in flight (find where that might be)
    VulkanRenderPass mFrontRenderPass;
    uint32_t mCurrentFrame;

    //TODO: re-architect this? seems weird, maybe switch to buffer src, buffer dst/imagedst? 
    // Will need to have KNOWLEDGE that the staging buffer for the object is now cleared though.
    struct dataTransfer{
        VulkanBuffer* src;
        VulkanBuffer* dst;
        VulkanImage* dstImage;
    };
    std::vector<dataTransfer> mCopyCommandQueue; //TODO: figure out async commands for transfer.
    

    VkDescriptorSetLayout mDescriptorSetLayout;//TODO: move temp to hold layout
    VkDescriptorSet mDescriptorSet; //TODO: move temp to hold the descriptor;
};

#endif // vulkan driver
