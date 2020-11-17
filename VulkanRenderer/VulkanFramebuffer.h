#ifndef VULKAN_FRAMEBUFFER_H
#define VULKAN_FRAMEBUFFER_H

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanImage.h"
#include "VulkanRenderPass.h"

//TODO: again this is probably going to be hashmap
class VulkanFramebuffer
{
public:
    VulkanFramebuffer();
    ~VulkanFramebuffer();
    void init(VkDevice device, uint32_t width, uint32_t height, const VulkanRenderPass &renderPass, const std::vector<VkImageView> &imageViews);
    void cleanup();

private:
    //TODO: figure out ownership of these images... do we want these here or outside? maybe multiple?
    VkDevice mDevice;
    VkFramebuffer mFramebuffer;
    std::vector<VkImageView> mAttachments; // may want multiple attachments
};

#endif