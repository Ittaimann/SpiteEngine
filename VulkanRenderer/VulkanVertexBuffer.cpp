#include "VulkanVertexBuffer.h"
#include "vk_mem_alloc.h"
#include "Core/ModelLoad.h"
VulkanVertexBuffer::VulkanVertexBuffer() {}
VulkanVertexBuffer::~VulkanVertexBuffer() {}

void VulkanVertexBuffer::init(const ModelLoad *model, VmaAllocator *alloc, bool staging)
{
    if(staging)
    {
        mStaging.init(alloc, (void *)model->getData().data(), model->getSize(), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_ONLY);
       
        VkBufferUsageFlags usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        mBuffer.init(alloc, nullptr, model->getSize(), usage, VMA_MEMORY_USAGE_GPU_ONLY);
    }
    else
    {
        VkBufferUsageFlags usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        mBuffer.init(alloc, (void *)model->getData().data(), model->getSize(), usage, VMA_MEMORY_USAGE_CPU_ONLY);
    }
    
}
void VulkanVertexBuffer::cleanup() {}

VkBuffer VulkanVertexBuffer::getVkBuffer()
{
    return mBuffer.getBuffer();
}

VulkanBuffer VulkanVertexBuffer::getBuffer()
{
    return mBuffer;
}

//TODO: reconsider this design decision. seems like i'm fighiting c++ but am I winning?
VulkanBuffer* VulkanVertexBuffer::getBufferPtr()
{
    return &mBuffer;
}

void VulkanVertexBuffer::unstageVertexBuffer(VkCommandBuffer commandBuffer)
{
    mBuffer.unstageBuffer(commandBuffer,mStaging);
}

void VulkanVertexBuffer::cleanupStaging()
{
    mStaging.cleanup();
}