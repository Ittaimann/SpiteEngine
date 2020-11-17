#ifndef VULKAN_RENDER_PASS_H
#define VULKAN_RENDER_PASS_H

#include <vulkan/vulkan.h>
//TODO: figure out if this is going to be a pool or an individual. for now it can be singular
class VulkanRenderPass
{
public:
    VulkanRenderPass();
    ~VulkanRenderPass();

    void init(VkDevice device);
    void cleanup();

    VkRenderPass getRenderPass() const;
private:
    VkRenderPass mRenderPass; //Consider turning this into a cache
    VkDevice mDevice;
};

#endif
