#define GLFW_INCLUDE_VULKAN //uh maybe a different place?
#include "WindowManager.h"
#include "Loader.h"
#include "VulkanRenderer/VulkanDriver.h"


//NEXT: create a vulkan buffer class, then start trying to load a model into that
//So buffers(done) => resource(need to expand,fix, and go back to... but done for now) => into buffers
//(maybe make a vertexBuffer class) => graphics pipeline
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
    
    VulkanDriver driver;
    driver.init(validation,&window);
    //driver.CreateModel(loaded); //
//TODO: render loop and exit from glfw input
    while(false)
    {
        // store all your graphics datas in the 
        // driver? nah hold it in the obejct? get to this in friendo and see
        //driver.draw();
    }
    driver.cleanup();
    
    window.cleanup();
    return 1;
}
