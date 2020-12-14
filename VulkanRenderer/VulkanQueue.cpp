#include "VulkanQueue.h"

VulkanQueue::VulkanQueue()
{}

VulkanQueue::~VulkanQueue()
{}

void VulkanQueue::init(VkDevice device,uint32_t family)
{
    vkGetDeviceQueue(device, family, 0, &mQueue);
}

void VulkanQueue::cleanup()
{}

VkQueue VulkanQueue::getQueue()
{
    return mQueue;
}
