#include "VulkanCommandPool.h"

VulkanCommandPool::VulkanCommandPool()
{
}

VulkanCommandPool::~VulkanCommandPool()
{
}
//TODO: alter vk queue to have an exclusive transfer queue that we can use and allocate for transfer operations.
void VulkanCommandPool::init(VkDevice device, uint32_t graphicsFamily)
{
    mDevice = device;
    VkCommandPoolCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo.queueFamilyIndex = graphicsFamily;
    createInfo.pNext = nullptr;
    createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    vkCreateCommandPool(device, &createInfo, nullptr, &mCommandPool);
    mCommandBuffer = VK_NULL_HANDLE;
}

void VulkanCommandPool::cleanup(VkDevice device)
{
    vkDestroyCommandPool(device, mCommandPool, nullptr);
}

void VulkanCommandPool::endFrame()
{
    mFreeCommandBufferQueue.insert(mFreeCommandBufferQueue.end(), mUsedCommandBufferQueue.begin(), mUsedCommandBufferQueue.end());
    mUsedCommandBufferQueue.clear();
}

VkCommandBuffer VulkanCommandPool::getCommandBuffer()
{
    if (mCommandBuffer == VK_NULL_HANDLE)
    {
        if (mFreeCommandBufferQueue.size() != 0)
        {
            VkCommandBuffer result = mFreeCommandBufferQueue.back();
            mFreeCommandBufferQueue.pop_back();
            return result;
        }
        else
        {
            return allocateCommandBuffer();
        }
    }
    return mCommandBuffer;
}

VkCommandBuffer VulkanCommandPool::allocateCommandBuffer()
{
    VkCommandBufferAllocateInfo commandBufferInfo = {};
    commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferInfo.pNext = NULL;
    commandBufferInfo.commandPool = mCommandPool;
    commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(mDevice, &commandBufferInfo, &commandBuffer);

    return commandBuffer;
}

//TODO: figure out if you want to be able to pass a specific one in here.
void VulkanCommandPool::beginRecording()
{
    VkCommandBufferBeginInfo commandBufferBeginInfo = {};
    commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBufferBeginInfo.pNext = nullptr;
    commandBufferBeginInfo.pInheritanceInfo = nullptr;
    commandBufferBeginInfo.flags = 0;
    VkCommandBuffer commandBufferRunning = getCommandBuffer();
    vkBeginCommandBuffer(commandBufferRunning, &commandBufferBeginInfo);
    mUsedCommandBufferQueue.push_back(commandBufferRunning);
    mCommandBuffer = commandBufferRunning;
}

void VulkanCommandPool::endRecording()
{
    vkEndCommandBuffer(mCommandBuffer);
    mCommandBuffer = VK_NULL_HANDLE;
}

std::vector<VkCommandBuffer> VulkanCommandPool::getUsedCommandBuffers()
{
    return mUsedCommandBufferQueue;
}