#ifndef VULKAN_HELPERS_H
#define VULKAN_HELPERS_H

#include <assert.h>
#include <vector>
#include <iostream>
#include <optional>

#define GLFW_INCLUDE_VULKAN //uh maybe a different place?
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace VulkanHelper
{

    //TODO: move these to config
    const std::vector<const char *> validationLayers = {"VK_LAYER_LUNARG_api_dump"};
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