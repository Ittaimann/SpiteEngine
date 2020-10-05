#ifndef VULKAN_HELPERS_H
#define VULKAN_HELPERS_H

#include <assert.h>
#include <vector>
#include <iostream>
#include <optional>

#include <vulkan/vulkan.h>

namespace VulkanHelper
{
    //TODO: do some serious dismantling of this file. Start with the extensions and validation
    // validationLayers used in instance and device, move to init.
    // deviceExtensions Used in physical device and device. Probably pass in init.
    // have these be optinos in the config
    const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    struct SwapChainSupportDetails 
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
}

#endif