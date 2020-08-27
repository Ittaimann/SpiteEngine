#define GLFW_INCLUDE_VULKAN
#include <assert.h>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <optional>
#include <set>

//TODO: remeber this is going to be you vulkan init-er for a long time. may want to really polish this
// its not glamourous, but it doesn't need to be efficient, just specific

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    //TODO: FIND A BETTER PLACE TO PUT THIS!!!
    return VK_FALSE;
}


namespace{
    VkInstance               VulkanInstance;
    VkSurfaceKHR             VulkanSurface;
    VkPhysicalDevice         VulkanPhysicalDevice;
    VkDevice                 VulkanDevice;
    VkQueue                  VulkanGraphicsQueue;
    VkQueue                  VulkanPresentQueue;
    VkCommandPool            VulkanCommandPool;
    VkDebugUtilsMessengerEXT VulkandebugMessenger;
   
    //queueFamilies
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    struct SwapChainSupportDetails {
	    VkSurfaceCapabilitiesKHR capabilities;
	    std::vector<VkSurfaceFormatKHR> formats;
	    std::vector<VkPresentModeKHR> presentModes;
    };

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

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) 
    {
        QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
        int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, VulkanSurface, &presentSupport);

			if (queueFamily.queueCount > 0 && presentSupport) {
				indices.presentFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
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

    void vkCreatePhysicalDevice(bool enableValidation)
    {
   		QueueFamilyIndices indices = findQueueFamilies(VulkanPhysicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

        VkPhysicalDeviceFeatures deviceFeatures = {};
		deviceFeatures.samplerAnisotropy = VK_TRUE;
		deviceFeatures.sampleRateShading = VK_TRUE; // enable sample shading feature for the device

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        //NEED TO GET THE QUEUE INFO 
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (enableValidation)
        {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
        {
			createInfo.enabledLayerCount = 0;
		}

        VkResult result = vkCreateDevice(VulkanPhysicalDevice, &createInfo, nullptr, &VulkanDevice);
        assert( result == VK_SUCCESS);

		vkGetDeviceQueue(VulkanDevice, indices.graphicsFamily.value(), 0, &VulkanGraphicsQueue);
		vkGetDeviceQueue(VulkanDevice, indices.presentFamily.value(), 0, &VulkanPresentQueue);

    }
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, VulkanSurface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, VulkanSurface, &formatCount, nullptr);

		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, VulkanSurface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, VulkanSurface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, VulkanSurface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}
    

	bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}


    bool isDeviceSuitable(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = findQueueFamilies(device);

		bool extensionsSupported = checkDeviceExtensionSupport(device);

		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}


		VkPhysicalDeviceFeatures supportedFeatures;
		vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

		return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;

    }
    void pickDevice()
    {
        uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(VulkanInstance, &deviceCount, nullptr);

		if (deviceCount == 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(VulkanInstance, &deviceCount, devices.data());

		for (const auto& device : devices) {
			if (isDeviceSuitable(device)) {
				VulkanPhysicalDevice = device;
				//TODO: support msaa
                //msaaSamples = getMaxUsableSampleCount();
				break;
			}
		}

		if (VulkanPhysicalDevice == VK_NULL_HANDLE) {
			throw std::runtime_error("failed to find a suitable GPU!");
		}
     }

     void vkCreateCommandPool()
     {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(VulkanPhysicalDevice);

         VkCommandPoolCreateInfo createInfo;
         createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
         createInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
         createInfo.pNext = nullptr;
         // I wanna reset able command buffer;
         createInfo.flags= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
     }

     bool init(bool EnableValidation,GLFWwindow* window)
     {
        // init debug messeger
        vkInitDevice(EnableValidation);
        
        //TODO: create the surface and window-ing;

        glfwCreateWindowSurface(VulkanInstance,window, nullptr, &VulkanSurface);
        pickDevice();
        // maybe pass in the vkSurface
        vkCreatePhysicalDevice(EnableValidation);
        vkCreateCommandPool();
        return VK_SUCCESS;

    }
    void shutdown()
    {

        vkDestroyCommandPool(VulkanDevice,VulkanCommandPool,nullptr);
        vkDestroyDevice(VulkanDevice,nullptr);
        if(VulkandebugMessenger!= VK_NULL_HANDLE) // maybe just cache the validation enable
            DestroyDebugUtilsMessengerEXT(VulkanInstance, VulkandebugMessenger, nullptr);
        vkDestroySurfaceKHR(VulkanInstance,VulkanSurface,nullptr);
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

    //TODO create a seperate window class, refactor start up to be clean and understandable
    // create a seperate header or cpp for this namespace, include it in the vulkan driver class.
    
    glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Spite", nullptr, nullptr);
	//glfwSetWindowUserPointer(window, this);
    std::cout<<"FIX GLFW WINDOW, MAKE A PROPER WINDOW CLASS"<<std::endl;

    std::cout<<"initing graphics state"<<std::endl;
    SPRenderState::init(true,window);
    SPRenderState::shutdown();

  	glfwDestroyWindow(window);
	glfwTerminate(); // maybe mose this else where?

    return 1;
}

