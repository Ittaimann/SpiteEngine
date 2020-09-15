#define GLFW_INCLUDE_VULKAN //uh maybe a different place?
#include <GLFW/glfw3.h>
#include "VulkanDriver.h"


int main()
{

    //TODO create a seperate window class, refactor start up to be clean and understandable
    // create a seperate header or cpp for this namespace, include it in the vulkan driver class.
    // also maybe make a config file, import the json file parser.
    
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    GLFWwindow *window = glfwCreateWindow(600, 600, "Spite", nullptr, nullptr);
    //glfwSetWindowUserPointer(window, this); //TODO: WHAT IS THIS MY
    std::cout << "FIX GLFW WINDOW, MAKE A PROPER WINDOW CLASS" << std::endl;
    
        
    //TODO: create an config file and toss this in there
    std::cout << "initing graphics state" << std::endl;
    
    bool validation = true;
    
    VulkanDriver driver;
    driver.init(validation,window);
    driver.cleanup();
    
    glfwDestroyWindow(window);
    glfwTerminate(); // maybe mose this else where?

    return 1;
}
