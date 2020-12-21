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
    void init(const ModelLoad* model, VmaAllocator* alloc);
    void cleanup();
    VkBuffer getVkBuffer();
    VulkanBuffer getBuffer();
private:
    VulkanBuffer mBuffer;
};

#endif