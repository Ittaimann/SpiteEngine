#define GLFW_INCLUDE_VULKAN
#include <assert.h>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    //TODO: FIND A BETTER PLACE TO PUT THIS!!!
    return VK_FALSE;
}


namespace{
    VkInstance               VulkanInstance;
    VkDevice                 VulkanDevice;
    VkPhysicalDevice         VulkanPhysicalDevice;
    VkQueue                  VulkanGraphicsQueue;
    VkQueue                  VulkanPresentQueue;
    VkCommandPool            VulkancommandPool;
    VkDebugUtilsMessengerEXT VulkandebugMessenger;
    
    //TODO: move validations into file i/o 
    // Don't want to recompile everytime... for strings
    const std::vector<const char*> validationLayers = {
	    "VK_LAYER_KHRONOS_validation"
    };
    //what does this do again? 
    const std::vector<const char*> deviceExtensions = {
	    VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	    if (func != nullptr) {
		    func(instance, debugMessenger, pAllocator);
	    }
    }
    std::vector<const char*> checkExtensions(VkInstanceCreateInfo &createInfo, bool enableValidationLayers)
    {
        uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
   		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
        return extensions;
    }

    VkDebugUtilsMessengerCreateInfoEXT InitValidationLayers(VkInstanceCreateInfo &createInfo)
    {
        uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}
			assert(layerFound); //WE DID NOT FIND A LAYER REQUESTED
		}

        // consider moving this out. We only need to check if these exist
        // why set it here?
        createInfo.enabledLayerCount =  validationLayers.size();
        createInfo.ppEnabledLayerNames = validationLayers.data();

        // create the debug validation
        
   		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        debugCreateInfo = {};
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = debugCallback;
        // object must persist 
        return debugCreateInfo;
    }

}

namespace SPRenderState
{
    //vulkan devices for init.
    // no window handling or surface
    // assume this is essentially static
    //TODO: get this namespace stuff reviewed. New tech
    VkResult vkInitDevice(bool enableValidation)
    {
        //TODO: Layers and extension handling is a mess.
        // Please try to clean this up and maybe make it into 
        // a runtime file you pass in a check
        assert(VulkanDevice == VK_NULL_HANDLE);
        VkResult result;
        
        VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Spite";
		appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.pEngineName = "SpiteEngine";
		appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

        std::vector<const char*> extensions = checkExtensions(createInfo,enableValidation);
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        // don't love this debug messenger handling, kinda messy.
        // its fine for now, but reconsider it on refactor, may want to seperate
        // it out just a bit
        VkDebugUtilsMessengerCreateInfoEXT debugInfo;
        if(enableValidation)
        {
           debugInfo = InitValidationLayers(createInfo);

           createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugInfo;
        }
        else
        {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        result = vkCreateInstance(&createInfo, nullptr, &VulkanInstance);

        if(enableValidation)
        {
            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
            debugCreateInfo = {};
		    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		    debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		    debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		    debugCreateInfo.pfnUserCallback = debugCallback;

            assert(CreateDebugUtilsMessengerEXT(VulkanInstance, &debugCreateInfo, nullptr, &VulkandebugMessenger)==VK_SUCCESS);
        }
        assert(result == VK_SUCCESS);
        return VK_SUCCESS;
    }

     bool init(bool EnableValidation)
    {
        // init debug messeger
        vkInitDevice(EnableValidation);
        
        //init device
        //init physical device
        // init queues
        //init command pool

        return VK_SUCCESS;

    }
    void shutdown()
    {
        if(VulkandebugMessenger!= VK_NULL_HANDLE) // maybe just cache the validation enable
            DestroyDebugUtilsMessengerEXT(VulkanInstance, VulkandebugMessenger, nullptr);
        vkDestroyInstance(VulkanInstance, nullptr);

        //destroy instance
        //destroy device
        //destroy physical device
        //destroy queues
        //destory command pool
        //destroy debug messenger
    }
    

}
int main()
{

    glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Spite", nullptr, nullptr);
	//glfwSetWindowUserPointer(window, this);
    std::cout<<"FIX GLFW WINDOW, MAKE A PROPER WINDOW CLASS"<<std::endl;

    std::cout<<"initing graphics state"<<std::endl;
    SPRenderState::init(true);
    SPRenderState::shutdown();

  	glfwDestroyWindow(window);
	glfwTerminate(); // maybe mose this else where?

    return 1;
}