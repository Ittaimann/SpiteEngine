#include "VulkanShader.h"

VulkanShader::VulkanShader()
{
}

VulkanShader::~VulkanShader()
{
    cleanup();
}

void VulkanShader::init(VkDevice device, uint32_t size,const void* code)
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
    if(mShaderModule!=VK_NULL_HANDLE){
        vkDestroyShaderModule(mDevice,mShaderModule,nullptr);
        mShaderModule = VK_NULL_HANDLE;
    }
}

VkShaderModule VulkanShader::getShaderModule() const
{
    return mShaderModule;
}
 
