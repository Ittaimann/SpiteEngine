#ifndef VULKAN_SURFACE_H
#define VULKAN_SURFACE_H

#include "VulkanHelpers.h"
#include <GLFW/glfw3.h>

class VulkanSurface
{
public:
    VulkanSurface(/* args */);
    ~VulkanSurface();
    void init(VkInstance instance, GLFWwindow *window);
    void cleanup(VkInstance instance);
    VkSurfaceKHR getVulkanSurface();
    
private:
    VkSurfaceKHR mSurface;
    /* data */
};

#endif