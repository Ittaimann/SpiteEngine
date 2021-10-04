#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

//This is going to be the object that holds and maintains the graphics state for the draw calls.
// game object is just transform this will be descriptors and shaders and all that, though probably
// will be mostly handles into maps as is appropriate
#include "glm/mat4x4.hpp"
#include "ShaderLoad.h"

//TODO: kill destroy remove
class VulkanDescriptor;
class VulkanShader;
class VulkanGraphicsPipeline;
class VulkanVertexBuffer;

class GraphicsObject
{
public:
    GraphicsObject();
    ~GraphicsObject();
    void init(const glm::mat4& initialTransform); 
    void cleanup();
    void updateMatrix(const glm::mat4& updatedTransform); 

    //TODO: find a better way to deal with this specifically. Either build out the 
    // non-api shader class, or start managing the api from the generic
    // Ugh I genericed to early...
    void setShader(/*const ShaderData shaderData,*/ShaderStage stage, VulkanShader* vulkanShader);
    void setPipline(VulkanGraphicsPipeline* pipeline);
    void setVertexBuffer(VulkanVertexBuffer* vertexBuffer);
    void setDescriptors( VulkanDescriptor* vulkanDescriptor);
private: 
    VulkanShader* vert;
    VulkanShader* frag;
    VulkanDescriptor* mDescriptor;
    VulkanGraphicsPipeline* mPipeline;
    VulkanVertexBuffer* mVertexBuffer;
};


#endif
