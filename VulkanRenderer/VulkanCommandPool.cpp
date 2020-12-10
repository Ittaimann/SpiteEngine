#include "VulkanCommandPool.h"

VulkanCommandPool::VulkanCommandPool()
{}

VulkanCommandPool::~VulkanCommandPool()
{}

void VulkanCommandPool::init(VkDevice device, uint32_t graphicsFamily)
{
    VkCommandPoolCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo.queueFamilyIndex = graphicsFamily;
    createInfo.pNext = nullptr;
    createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT; 
    vkCreateCommandPool(device,&createInfo,nullptr,&mCommandPool);


    VkCommandBufferAllocateInfo commandBufferInfo = {};
    commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferInfo.pNext = NULL;
    commandBufferInfo.commandPool = mCommandPool;
    commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferInfo.commandBufferCount = 1;

    vkAllocateCommandBuffers(device, &commandBufferInfo, &mCommandBuffer);

}

void VulkanCommandPool::cleanup(VkDevice device)
{
    vkDestroyCommandPool(device, mCommandPool, nullptr);

}
VkCommandBuffer VulkanCommandPool::getCommandBuffer()
{
    return mCommandBuffer;
}