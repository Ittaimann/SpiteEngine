#include "VulkanSurface.h"

VulkanSurface::VulkanSurface()
{}

VulkanSurface::~VulkanSurface()
{}

void VulkanSurface::init(VkInstance instance,GLFWwindow *window)
{
    glfwCreateWindowSurface(instance, window, nullptr, &mSurface);
}

void VulkanSurface::cleanup()
{}

VkSurfaceKHR VulkanSurface::getVulkanSurface()
{
    return mSurface;
}