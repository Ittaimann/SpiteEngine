#define GLFW_INCLUDE_VULKAN //uh maybe a different place?
#include "Core/WindowManager.h"
#include "Core/Loader.h"
//TODO: clean up this file so that we don't need to worry so much about including extra vulkan stuff
#include "VulkanRenderer/VulkanRenderer.h"



//NEXT: SHADERS => graphics pipeline
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

    //TODO: REMOVE VULKAN BLEEDING OUT HERE, might need to alter this once I get more generic classes. return "renderpass", "frame buffer", and "image"
    // and pass those into the renderer as like a "build the driver version", then return a pointer to the default?
    // Maybe have it so that its a struct of data we pass into the apis and  then have a driver pointer attach
    {
        VulkanRenderPass renderpass;
        renderer.buildRenderPass(renderpass);
        VulkanImage depthBuffer;
        renderer.buildImage(depthBuffer,480, 320, VK_FORMAT_D24_UNORM_S8_UINT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_IMAGE_ASPECT_DEPTH_BIT);
        VulkanFramebuffer framebuffer;
        renderer.buildFramebuffer(framebuffer,480,320,renderpass,depthBuffer);
        VulkanGraphicsPipeline pipeline;
        renderer.buildPipeline(pipeline,renderpass);
    }

//TODO: render loop and exit from glfw input
    while(false)
    {
        // store all your graphics datas in the hello
        // driver? nah hold it in the obejct? get to this in friendo and see
        //driver.draw();
    }
    renderer.cleanup();
    
    window.cleanup();
    return 1;
}
