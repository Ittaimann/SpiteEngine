#include "VulkanDescriptor.h"

VulkanDescriptor::VulkanDescriptor()
: mBindingLocation(0), mDescriptor(VK_NULL_HANDLE),mLayout(VK_NULL_HANDLE)
{
    (void)mBindingLocation;
}

VulkanDescriptor::~VulkanDescriptor()
{}

void VulkanDescriptor::init(ShaderData& data)
{
    (void)data;

//    VkDescriptorSetLayoutBinding layoutBindingInfo[2];
//    layoutBindingInfo[0].binding = 0;
//    layoutBindingInfo[0].descriptorCount = 1;
//    layoutBindingInfo[0].pImmutableSamplers = nullptr;
//    layoutBindingInfo[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//    layoutBindingInfo[0].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
//
//    layoutBindingInfo[1].binding = 1;
//    layoutBindingInfo[1].descriptorCount = 1;
//    layoutBindingInfo[1].pImmutableSamplers = nullptr;
//    layoutBindingInfo[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//    layoutBindingInfo[1].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
//    
//    VkDescriptorSetLayoutCreateInfo layoutInfo = {};
//    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
//    layoutInfo.pNext = nullptr;
//    layoutInfo.flags = 0;
//    layoutInfo.bindingCount = 2;
//    layoutInfo.pBindings = layoutBindingInfo;
//    
//    //NOTE: FOR NEXT TIME:
//    //this DOES NOT return multiple descriptor set layouts. You only need 1
//    // it has the same bindings in here so its ok to do 1, just be aware to 
//    // make the alterations to the pipeline as well.`
//    VkResult lmao = vkCreateDescriptorSetLayout(mDevice.getDevice(), &layoutInfo, nullptr, mDescriptorSetLayout)
//    assert(lmao == VK_SUCCESS);
//    // build descriptor
//    // descriptor allocation seems to be kinda silly?
////    mDescriptorSetLayout[1] = mDescriptorSetLayout[0];
//
//    VkDescriptorSetAllocateInfo descriptorAllocInfo = {};
//    descriptorAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
//    descriptorAllocInfo.pNext = nullptr;
//    descriptorAllocInfo.descriptorPool = mDescriptorPool;
//    descriptorAllocInfo.descriptorSetCount = 1;
//    descriptorAllocInfo.pSetLayouts = mDescriptorSetLayout;
//    //NOTE FOR FUTURE ITTAI: the crash is because the descriptor set alloc info is
//    // expecting 2 descriptor setLayous most likely and thats
//    // why its dying, its attempting to access descriptor set layout 2 which doesn't exist
//    // why is there two descriptor sets though? seems like I probably don't need both?
//    // like what does my vertex shader look like?
//    lmao = vkAllocateDescriptorSets(mDevice.getDevice(), &descriptorAllocInfo, mDescriptorSet);
//
//    assert(lmao == VK_SUCCESS);
}

void VulkanDescriptor::cleanup()
{}
