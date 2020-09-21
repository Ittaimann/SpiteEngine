#define GLFW_INCLUDE_VULKAN //uh maybe a different place?
#include "WindowManager.h"
#include "VulkanRenderer/VulkanDriver.h"


int main()
{

    //TODO create a seperate window class, refactor start up to be clean and understandable
    // create a seperate header or cpp for this namespace, include it in the vulkan driver class.
    // also maybe make a config file, import the json file parser.
    WindowManager window;
    window.init(600,600);
    
    bool validation = true;
    
    VulkanDriver driver;
    driver.init(validation,&window);
    driver.cleanup();
    
    window.cleanup();
    return 1;
}
