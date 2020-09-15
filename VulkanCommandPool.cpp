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
}

void VulkanCommandPool::cleanup(VkDevice device)
{
    vkDestroyCommandPool(device, mCommandPool, nullptr);

}