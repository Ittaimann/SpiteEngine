#include "VulkanPhysicalDevice.h"
#include <set>
#include <string>

//TODO: organize this file a little bit...a lot a bit
VulkanHelper::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    VulkanHelper::QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    int i = 0;
    for (const auto &queueFamily : queueFamilies)
    {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if (queueFamily.queueCount > 0 && presentSupport)
        {
            indices.presentFamily = i;
        }

        if (indices.isComplete())
        {
            break;
        }

        i++;
    }

    return indices;
}

bool checkDeviceExtensionSupport(VkPhysicalDevice device)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(VulkanHelper::deviceExtensions.begin(), VulkanHelper::deviceExtensions.end());

    for (const auto &extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

//TODO: move this to vulkanswapchain? and pass it down probably that? keep in vulkan helper? store the end result?
// if I store it then I can take all the helpers and put them in here 🤔.

VulkanHelper::SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    VulkanHelper::SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0)
    {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}
bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    VulkanHelper::QueueFamilyIndices indices = findQueueFamilies(device, surface);

    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported)
    {
        VulkanHelper::SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

    return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

VkPhysicalDevice FindGraphicsDevice(VkInstance instance, VkSurfaceKHR surface)
{
    VkPhysicalDevice result;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    assert(deviceCount != 0); // failed to find any device

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (int i = 0; i < devices.size(); i++)
    {
        if (isDeviceSuitable(devices[i], surface))
        {
            result = devices[i];
            break;
            //TODO: support msaa
        }
    }
    assert(result != VK_NULL_HANDLE); // failed to appropriate device
    return result;
}

VulkanPhysicalDevice::VulkanPhysicalDevice()
{
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

void VulkanPhysicalDevice::init(VkInstance instance, VkSurfaceKHR surface)
{
    mPhysicalDevice = FindGraphicsDevice(instance, surface);
    mQueueFamilies = findQueueFamilies(mPhysicalDevice, surface);
    mSwapChainDetails = querySwapChainSupport(mPhysicalDevice,surface);
}

void VulkanPhysicalDevice::cleanup()
{}

VulkanHelper::QueueFamilyIndices VulkanPhysicalDevice::getFamilyIndices()
{
    return mQueueFamilies;
}

VkPhysicalDevice VulkanPhysicalDevice::getPhysicalDevice()
{
    return mPhysicalDevice;
}

VulkanHelper::SwapChainSupportDetails VulkanPhysicalDevice::getSwapChainDetails()
{
    return mSwapChainDetails;
}
