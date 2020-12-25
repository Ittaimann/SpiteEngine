#ifndef VULKAN_VERTEX_BUFFER_H
#define VULKAN_VERTEX_BUFFER_H

#include "VulkanBuffer.h"

class ModelLoad; // optimize: do we need model load? we could probably break down to components earlier?
class vmaAllocator;

class VulkanVertexBuffer
{
public:
    VulkanVertexBuffer();
    ~VulkanVertexBuffer();
    void init(const ModelLoad* model, VmaAllocator* alloc, bool staging);
    void cleanup();
    VkBuffer getVkBuffer();
    VulkanBuffer getBuffer();
    VulkanBuffer* getBufferPtr();
    //TODO: revist some of this staging and unstaging stuff. seems like this definitly needs to cleaned up.
    void unstageVertexBuffer(VkCommandBuffer);
    void cleanupStaging();

private:
    VulkanBuffer mBuffer;
    VulkanBuffer mStaging;
};

#endif