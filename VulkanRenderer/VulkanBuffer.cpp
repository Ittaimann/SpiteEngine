#include "VulkanBuffer.h"
#include <assert.h>
#include <string.h>
VulkanBuffer::VulkanBuffer()
{
}

VulkanBuffer::~VulkanBuffer()
{
    cleanup();
}

void VulkanBuffer::init(VmaAllocator *allocator, void *data, uint32_t size, VkBufferUsageFlags usage, VmaMemoryUsage VmaUsage)
{
    mAllocator = allocator;
    mBuffer = VK_NULL_HANDLE;

    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;

    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VmaUsage;
    allocInfo.pUserData = data;
    VkResult result = vmaCreateBuffer(*allocator, &bufferInfo, &allocInfo, &mStagingBuffer, &mVmaAlloc, nullptr);
    assert(result == VK_SUCCESS);

    mSize = size;

    void *mapdata;
    vmaMapMemory(*allocator, mVmaAlloc, &mapdata);
    memcpy(mapdata, data, (size_t)size);
    vmaUnmapMemory(*allocator, mVmaAlloc);
}

void VulkanBuffer::cleanup()
{
    if (mBuffer != VK_NULL_HANDLE)
    {
        vmaDestroyBuffer(*mAllocator, mBuffer, mVmaAlloc);
        mBuffer = VK_NULL_HANDLE;
    }
    if (mStagingBuffer != VK_NULL_HANDLE)
    {
        vmaDestroyBuffer(*mAllocator, mStagingBuffer, mVmaAlloc);
        mStagingBuffer = VK_NULL_HANDLE;
    }
}

VkBuffer VulkanBuffer::getBuffer()
{
    if (mBuffer != VK_NULL_HANDLE)
    {
        return mBuffer;
    }
    return mStagingBuffer;
}

//NEXT: fix this stuff, this staging buffer stuff might need to get moved up the chain to make 
// the usage bits make sense for the vkBuffer. maybe have a staging buffer and update buffer
// on the thing holding this and then have the buffer users update it? But how do I cache 
// those commands? Am I going to need to do function pointers ffs
void VulkanBuffer::unstageBuffer(VkCommandBuffer commandBuffer)
{
    VkBufferCopy bufferCopy = {};
    bufferCopy.dstOffset = 0;
    bufferCopy.srcOffset = 0;
    bufferCopy.size = mSize;
    vkCmdCopyBuffer(commandBuffer, mStagingBuffer, mBuffer, 1, &bufferCopy);
    vmaDestroyBuffer(*mAllocator, mStagingBuffer, mVmaAlloc);
    mStagingBuffer = VK_NULL_HANDLE;
}
