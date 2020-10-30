#include "VulkanBuffer.h"
#include <assert.h>

VulkanBuffer::VulkanBuffer()
{
}

VulkanBuffer::~VulkanBuffer()
{
}

void VulkanBuffer::init(VmaAllocator allocator, void* data, uint32_t size, VmaMemoryUsage usage)
{
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;

    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = usage;

    VkResult result = vmaCreateBuffer(allocator, &bufferInfo, &allocInfo, &mBuffer, &mVmaAlloc, nullptr);
    assert(result == VK_SUCCESS);

    mSize = size;
    //TODO: figure out how you want to handle the input to the buffer and the mapping.    
}

void VulkanBuffer::cleanup(VmaAllocator allocator)
{
    vmaDestroyBuffer(allocator, mBuffer, mVmaAlloc);
}