#ifndef VULKAN_DESCRIPTOR_H
#define VULKAN_DESCRIPTOR_H

//TODO: remove once you have more includes, just need it for uint32_t
#include <stdint.h>

class VulkanDescriptor
{
public:
    VulkanDescriptor();
    ~VulkanDescriptor();

    void init();
    void cleanup();

private:    
    uint32_t mBindingLocation;
};



#endif
