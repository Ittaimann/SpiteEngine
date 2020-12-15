#include "VulkanRenderPass.h"
#include <assert.h>
//https://www.saschawillems.de/blog/2018/07/19/vulkan-input-attachments-and-sub-passes/
VulkanRenderPass::VulkanRenderPass()
{
}
VulkanRenderPass::~VulkanRenderPass()
{
    cleanup();
}

//TODO: build a proper init for description creation. for now this only works for front buffer
void VulkanRenderPass::init(VkDevice device)
{
    mDevice = device;
    //TODO: adjust these as necessary and add more args to allow for greater flex
    // renderpasses largly will be an at start thing so go wild.

    //For now its just two as we only have the main render pass
    // color attachment => present
    VkAttachmentDescription attachmentDesc[1] = {};
    attachmentDesc[0].flags = 0;
    attachmentDesc[0].format = VK_FORMAT_B8G8R8A8_UNORM;
    attachmentDesc[0].samples = VK_SAMPLE_COUNT_1_BIT; //msaa?
    attachmentDesc[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDesc[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; //TODO: write to a back buffer, this is writing directly to swap chain
    attachmentDesc[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDesc[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDesc[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDesc[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    VkAttachmentReference color = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    // //depth attachement
    // attachmentDesc[1].flags = 0;
    // attachmentDesc[1].format = VK_FORMAT_D24_UNORM_S8_UINT;
    // attachmentDesc[1].samples = VK_SAMPLE_COUNT_1_BIT; //msaa?
    // attachmentDesc[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    // attachmentDesc[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL; // present this for now
    // attachmentDesc[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    // attachmentDesc[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    // attachmentDesc[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    // attachmentDesc[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    // VkAttachmentReference depth = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

    //Knowledge: learn what each of these attachents are (specifically preserve?)
    VkSubpassDescription subPassDesc = {};
    subPassDesc.flags = 0;
    subPassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subPassDesc.inputAttachmentCount = 0;
    subPassDesc.pInputAttachments = nullptr;
    subPassDesc.colorAttachmentCount = 1;
    subPassDesc.pColorAttachments = &color;
    subPassDesc.pResolveAttachments = 0;
    subPassDesc.pDepthStencilAttachment = nullptr;//&depth;
    subPassDesc.preserveAttachmentCount = 0;
    subPassDesc.pPreserveAttachments = nullptr;

    //Knowledge: learn more about subpass and dependecies. seems strong
    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.flags = 0;
    renderPassInfo.pNext = nullptr;
    renderPassInfo.attachmentCount = 1; //color
    renderPassInfo.pAttachments = attachmentDesc;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subPassDesc;
    renderPassInfo.dependencyCount = 0; // what is this?
    renderPassInfo.pDependencies = nullptr;

    VkResult result = vkCreateRenderPass(device, &renderPassInfo, nullptr, &mRenderPass);
    assert(result == VK_SUCCESS);
}
void VulkanRenderPass::cleanup()
{
    if (mRenderPass != VK_NULL_HANDLE)
    {
        vkDestroyRenderPass(mDevice, mRenderPass, nullptr);
        mRenderPass = VK_NULL_HANDLE;
    }
}

VkRenderPass VulkanRenderPass::getRenderPass() const
{
    return mRenderPass;
}