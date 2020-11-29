#include "VulkanShader.h"

VulkanShader::VulkanShader()
{
}

VulkanShader::~VulkanShader()
{
    cleanup();
}

void VulkanShader::init(VkDevice device, uint32_t size, void* code)
{
    mDevice = device;
    VkShaderModuleCreateInfo shaderModuleInfo = {};
    shaderModuleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleInfo.pNext = nullptr;
    shaderModuleInfo.flags = 0;
    shaderModuleInfo.codeSize = size;
    shaderModuleInfo.pCode = reinterpret_cast<const uint32_t*>(code);
    vkCreateShaderModule(mDevice,&shaderModuleInfo,nullptr,&mShaderModule);
}

void VulkanShader::cleanup()
{
    vkDestroyShaderModule(mDevice,mShaderModule,nullptr);
}

VkShaderModule VulkanShader::getShaderModule()
{
    return mShaderModule;
}