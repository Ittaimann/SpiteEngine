#ifndef VULKAN_SHADER_H
#define VULKAN_SHADER_H

#include <vulkan/vulkan.h>
//TODO: this file is maybe a bit much. seems like I could probably get away without this? though maybe I turn this into vulkan material?
// figure out whether or not this is gonna hold both vert and frag or everthing. 
class VulkanShader
{
public:
VulkanShader();
~VulkanShader();

void init(VkDevice device, uint32_t size, void* code);
void cleanup();

VkShaderModule getShaderModule();

private:
VkShaderModule mShaderModule;
VkDevice mDevice;
};

#endif