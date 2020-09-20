#include "VulkanDevice.h"
#include <set>
VulkanDevice::VulkanDevice()
{}

VulkanDevice::~VulkanDevice()
{}

void VulkanDevice::init(bool enableValidation,VkPhysicalDevice physicalDevice,VulkanHelper::QueueFamilyIndices indices)
{

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures = {};
        deviceFeatures.samplerAnisotropy = VK_TRUE;
        deviceFeatures.sampleRateShading = VK_TRUE; // enable sample shading feature for the device

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        //NEED TO GET THE QUEUE INFO
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(VulkanHelper::deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = VulkanHelper::deviceExtensions.data();

        if (enableValidation)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanHelper::validationLayers.size());
            createInfo.ppEnabledLayerNames = VulkanHelper::validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &mDevice);
        assert(result == VK_SUCCESS);
}

void VulkanDevice::cleanup()
{
    vkDestroyDevice(mDevice, nullptr);
}

VkDevice VulkanDevice::getDevice()
{
    return mDevice;
}