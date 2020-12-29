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
    
    //TODO: getting pointers vs getting reference is getting annoying. Fix you desctructor
    VulkanBuffer getBuffer();
    VulkanBuffer* getBufferPtr();
    VulkanBuffer* getStagingPtr();

private:
    VulkanBuffer mBuffer;
    VulkanBuffer mStaging;
};

#endif