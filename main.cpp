#include "Core/WindowManager.h"
#include "Core/Loader.h"
//TODO: clean up this file so that we don't need to worry so much about including extra vulkan stuff.
#include "VulkanRenderer/VulkanRenderer.h"

//NEXT: Get the command buffer submission and sync handled.
// TODO: get a code review...
int main()
{
    //TODO: config file
    bool validation = true;

    WindowManager window;
    window.init(480, 320);

    // TODO: Figure out a standard way to deal with paths to the cache.
    Loader loader;
    ModelLoad loaded = loader.loadModel("../../Assets/glTF-Sample-Models/2.0/TriangleWithoutIndices/glTF/TriangleWithoutIndices.gltf");
    ShaderLoad vert = loader.loadShader("../../AssetCache/vert.spv");
    ShaderLoad frag = loader.loadShader("../../AssetCache/frag.spv");

    VulkanRenderer renderer;
    renderer.init(validation, &window);

    //TODO: REMOVE VULKAN BLEEDING OUT HERE, might need to alter this once I get more generic classes. return "renderpass", "frame buffer", and "image"
    // and pass those into the renderer as like a "build the driver version", then return a pointer to the default?
    // Maybe have it so that its a struct of data we pass into the apis and  then have a driver pointer attach
    {
        VulkanRenderPass renderpass;
        renderer.buildRenderPass(renderpass);
        VulkanImage depthBuffer;
        renderer.buildImage(depthBuffer, 480, 320, VK_FORMAT_D24_UNORM_S8_UINT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_IMAGE_ASPECT_DEPTH_BIT);
        VulkanFramebuffer framebuffer;
        renderer.buildFramebuffer(framebuffer, 480, 320, renderpass, depthBuffer);
        VulkanGraphicsPipeline pipeline;
        std::vector<VulkanShader> shaders(2);
        renderer.buildShader(shaders[0], &vert);
        renderer.buildShader(shaders[1], &frag);
        renderer.buildPipeline(pipeline, renderpass, shaders);
        VulkanVertexBuffer vertexBuffer;
        renderer.buildModel(vertexBuffer,&loaded);
        //TODO: render loop and exit from glfw input
        while (window.getWindowClosed())
        {
            window.pollEvents();
            renderer.beginFrame();
            renderer.beginRenderPass(renderpass,framebuffer);

            renderer.bindVertexBuffer(vertexBuffer);
            renderer.bindPipeline(pipeline)
            renderer.draw();

            renderer.endRenderPass();
            renderer.endFrame();
        }
    }
    renderer.cleanup();

    window.cleanup();
    return 1;
}
