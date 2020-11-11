#include "VulkanRenderPass.h"



//https://www.saschawillems.de/blog/2018/07/19/vulkan-input-attachments-and-sub-passes/
VulkanRenderPass::VulkanRenderPass()
{
}
VulkanRenderPass::~VulkanRenderPass()
{
}

void VulkanRenderPass::init(VkDevice device)
{
    //TODO: adjust these as necessary and add more args to allow for greater flex
    // renderpasses largly will be an at start thing so go wild.

    //For now its just two as we only have the main render pass
    // color attachment => present
    VkAttachmentDescription attachmentDesc[2] = {};
    attachmentDesc[0].flags = 0;
    attachmentDesc[0].format = VK_FORMAT_B8G8R8A8_UNORM;
    attachmentDesc[0].samples = VK_SAMPLE_COUNT_1_BIT; //msaa?
    attachmentDesc[0].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachmentDesc[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; // present this for now
    attachmentDesc[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDesc[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDesc[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDesc[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    //depth attachemtn
    attachmentDesc[1].flags = 0;
    attachmentDesc[1].format = VK_FORMAT_D24_UNORM_S8_UINT;
    attachmentDesc[1].samples = VK_SAMPLE_COUNT_1_BIT; //msaa?
    attachmentDesc[1].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachmentDesc[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL; // present this for now
    attachmentDesc[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDesc[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDesc[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDesc[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.flags = 0;
    renderPassInfo.pNext = nullptr;
    renderPassInfo.attachmentCount = 2; //color and depth
    renderPassInfo.pAttachments = attachmentDesc;
    renderPassInfo.subpassCount = 0; // optimize: learn how these work properly;
    renderPassInfo.pSubpasses = nullptr; //TODO: subPasses
    renderPassInfo.dependencyCount = 0; // what is this?
    renderPassInfo.pDependencies = nullptr;

    vkCreateRenderPass(device, &renderPassInfo, nullptr, &mRenderPass);
}
void VulkanRenderPass::cleanup()
{
}