#ifndef VULKAN_FRAMEBUFFER_H
#define VULKAN_FRAMEBUFFER_H

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanImage.h"
#include "VulkanRenderPass.h"

class VulkanFramebuffer
{
public:
    VulkanFramebuffer();
    ~VulkanFramebuffer();
    void init(VkDevice device, uint32_t width, uint32_t height, const VulkanRenderPass &renderPass, const std::vector<VkImageView> &imageViews);
    void init(VkDevice device, uint32_t width, uint32_t height, const VulkanRenderPass &renderPass, VkImageView imageViews);

    void cleanup();

    VkFramebuffer getFramebuffer();
    VkRect2D getRenderArea();

private:
    //TODO: figure out ownership of these images... do we want these here or outside? maybe multiple?
    VkDevice mDevice;
    VkFramebuffer mFramebuffer;
    VkRect2D mRenderArea;
    std::vector<VkImageView> mAttachments; // may want multiple attachments
};

#endif