#ifndef VULKAN_RENDER_PASS_H
#define VULKAN_RENDER_PASS_H

#include <vulkan/vulkan.h>
//going to be pooled in main
class VulkanRenderPass
{
public:
    VulkanRenderPass();
    ~VulkanRenderPass();

    void init(VkDevice device);
    void cleanup();

    VkRenderPass getRenderPass() const;

private:
    VkSubpassDescription createSubPassDescription(VkAttachmentReference *attachmentReference);
    VkAttachmentDescription createAttachmentDescription();
    VkRenderPass mRenderPass;
    VkDevice mDevice;
};

#endif
