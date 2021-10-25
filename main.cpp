#include "Core/Camera.h"
#include "Core/GameObject.h"
#include "Core/InputManager.h"
#include "Core/Loader.h"
#include "Core/WindowManager.h"
// TODO: clean up this file so that we don't need to worry so much about
// including extra vulkan stuff.

#include "VulkanRenderer/VulkanRenderer.h"

const uint32_t WIDTH = 480;
const uint32_t HEIGHT = 320;
// REFACTOR: get the framebuffer,renderpass, and pipeline interop better.
// Instead of writing to a front buffer all the time write to a back buffer and
// flush to front REFACTOR: find where you are using constnats and stop doing
// that. properly set things. REFACTOR: error handling inside the renderer needs
// to happen. Right now we are just flying and that is a mega mistake. shit
// could be dying badly. REFACTOR: consider figuring out a better way to do
// passing stuff in. I'm getting sick and tired of having brain confusion over &
// and * this is a symptom of the destructors
// TODO: get a code review...
// NEXT: Camera/camera controls, load an index buffer model.
int main() {
    // TODO: config file
    bool validation = true;

    WindowManager window;
    window.init(WIDTH, HEIGHT);
    InputManager *input = InputManager::getInputManger();
    input->init(&window);

    // TODO: Figure out a standard way to deal with paths to the cache.
    Loader loader;
    ModelLoad loaded = loader.loadModel("Assets/glTF-Sample-Models/2.0/TriangleWithoutIndices/glTF/TriangleWithoutIndices.gltf");
    //need some meta data around these shaders...
    ShaderLoad vert = loader.loadShader("AssetCache/vert.spv");
    ShaderLoad frag = loader.loadShader("AssetCache/frag.spv");    

    VulkanRenderer renderer;
    renderer.init(validation, &window);

    // TODO: REMOVE VULKAN BLEEDING OUT HERE, might need to alter this once I
    // get more generic classes. return "renderpass", "frame buffer", and
    // "image" and pass those into the renderer as like a "build the driver
    // version", then return a pointer to the default? Maybe have it so that its
    // a struct of data we pass into the apis and  then have a driver pointer
    // attach
    {

        std::vector<VulkanShader> shaders(2);
        renderer.buildShader(shaders[0], &vert);
        renderer.buildShader(shaders[1], &frag); 

        // TODO: prebuild the descriptor, its needed for the pipeline
        // pass in camera descriptor set styling here I guess?
        renderer.buildDescriptorSet(2);
        VulkanGraphicsPipeline pipeline;
        renderer.buildPipeline(pipeline, *renderer.getFrontRenderPass(), shaders); 
        VulkanVertexBuffer vertexBuffer;
        renderer.buildModel(vertexBuffer, &loaded, true);
        VulkanDescriptor descriptors;
        // buffer for the position data
        VulkanBuffer cameraLoc;
        renderer.buildBuffer(cameraLoc, sizeof(glm::vec3), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT);

        // TODO:Find a way to asset this 
        GameObject triangle;
        triangle.getGraphicsObject().setShader(ShaderStage::VERTEX,&shaders[0]); 
        triangle.getGraphicsObject().setShader(ShaderStage::FRAGMENT,&shaders[1]);
        triangle.getGraphicsObject().setVertexBuffer(&vertexBuffer);
        triangle.getGraphicsObject().setPipline(&pipeline);
        triangle.getGraphicsObject().setDescriptors();
        Camera mainCamera;
        mainCamera.init(WIDTH, HEIGHT);

        while (window.getWindowClosed()) {
            // input
            window.pollEvents();
            mainCamera.update();
            // NEXT: get the object main camera and object's model to view, the
            // projection matrix; currently following this tutorial:
            // https://learnopengl.com/Getting-started/Camera to get camera
            // ideas down;
            glm::mat4 cameraView = mainCamera.getView();
            glm::mat4 camerPerspective = mainCamera.getProjection();
            glm::mat4 gameObjectTransform = triangle.getTransform();
            

            // need descriptor for perspective, view, and model location;
            // write all to same buffer?
            // while thats probably the better idea, i want the practice and to write
            // more descriptor code just for understanding.
           
            cameraLoc.writeToBuffer(static_cast<void *>(&cameraView), sizeof(glm::mat4));
            renderer.updateDescriptors(2, &cameraLoc);
            // pool might just be a kinda singleton(?), where we have different
            // descriptor pools in it layout is just hand written for now. might
            // need to rely on spriv reflection, then based on material meta
            // data set is hand coded, then reliant on spirv reflection, then
            // probably meta data based on material meta data.

            // rendering
            renderer.beginFrame();
            renderer.beginRecording();
            renderer.beginRenderPass(*renderer.getFrontRenderPass(),
                                     *renderer.getFrontBuffer());
            renderer.bindVertexBuffer(vertexBuffer);
            renderer.bindPipeline(pipeline);
            renderer.bindDescriptorSet(pipeline);
            // set camera location, maybe set up a graphics data class and pass
            // that the camera
            renderer.draw();
            renderer.endRenderPass();
            renderer.endRecording();
            renderer.endFrame();
        }
    }

    renderer.cleanup();
    input->cleanup();
    window.cleanup();
    return 0;
}
