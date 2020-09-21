#include "VulkanSurface.h"

VulkanSurface::VulkanSurface()
{}

VulkanSurface::~VulkanSurface()
{}

void VulkanSurface::init(VkInstance instance,GLFWwindow *window)
{
        glfwCreateWindowSurface(instance, window, nullptr, &mSurface);
}

void VulkanSurface::cleanup(VkInstance instance)
{
    vkDestroySurfaceKHR(instance,mSurface,nullptr);
}

VkSurfaceKHR VulkanSurface::getVulkanSurface()
{
    return mSurface;
}