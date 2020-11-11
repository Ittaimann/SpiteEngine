find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)


add_library(
    VulkanDriver 
    VulkanRenderer.cpp
    VulkanInstance.cpp
    VulkanDevice.cpp
    VulkanCommandPool.cpp
    VulkanQueue.cpp
    VulkanSurface.cpp
    VulkanPhysicalDevice.cpp
    VulkanSwapChain.cpp
    VulkanBuffer.cpp
    VulkanVertexBuffer.cpp
    VulkanImage.cpp
    VulkanRenderPass.cpp
)

target_link_libraries(VulkanDriver glfw ${GLFW_LIBRARIES} Vulkan::Vulkan)