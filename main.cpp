#define GLFW_INCLUDE_VULKAN //uh maybe a different place?
#include "WindowManager.h"
#include "Loader.h"
#include "VulkanRenderer/VulkanRenderer.h"


//TODO: remove these/generic these? also make sure that if we don't use vulkan don't include it?
#include "VulkanRenderer/VulkanFramebuffer.h"
#include "VulkanRenderer/VulkanRenderPass.h"

//NEXT: framebuffer object=>SHADERS => graphics pipeline
//Then build vulkan texture class to allocate frame buffers from.
//once the graphics pipeline is all done revisit window resize.
// The camera

// TODO: get a code review...
int main()
{
    Loader loader;
    ModelLoad loaded = loader.loadModel("../../Assets/glTF-Sample-Models/2.0/TriangleWithoutIndices/glTF/TriangleWithoutIndices.gltf");
    //TODO: config file
    WindowManager window;
    window.init(480,320);
    
    bool validation = true;
    
    VulkanRenderer renderer;
    renderer.init(validation,&window);
    renderer.buildModel(&loaded);

    //TODO: REMOVE VULKAN BLEEDING OUT HERE 
    VulkanRenderPass renderpass;
    renderer.buildRenderPass(renderpass);
    VulkanImage depthBuffer;
    renderer.buildImage(depthBuffer,480, 320, VK_FORMAT_D24_UNORM_S8_UINT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_IMAGE_ASPECT_DEPTH_BIT);
    VulkanFramebuffer framebuffer = renderer.buildFramebuffer(480,320,renderpass,depthBuffer);
    depthBuffer.cleanup();
    renderpass.cleanup();

//TODO: render loop and exit from glfw input
    while(false)
    {
        // store all your graphics datas in the 
        // driver? nah hold it in the obejct? get to this in friendo and see
        //driver.draw();
    }
    renderer.cleanup();
    
    window.cleanup();
    return 1;
}
