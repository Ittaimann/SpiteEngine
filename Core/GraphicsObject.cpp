#include "GraphicsObject.h"


GraphicsObject::GraphicsObject()
{}

GraphicsObject::~GraphicsObject()
{}

void GraphicsObject::init(const glm::mat4 &initialTransform)
{
    (void)initialTransform;
}

void GraphicsObject::cleanup()
{}

void GraphicsObject::updateMatrix(const glm::mat4 &updatedTransform)
{
    (void)updatedTransform;
}

void GraphicsObject::setShader(/*const ShaderData shaderData*/ShaderStage stage, VulkanShader *vulkanShader)
{
    switch (stage) {
        case VERTEX:
            vert = vulkanShader;
            break;
        case FRAGMENT:
            frag = vulkanShader;
            break;
    }
}

void GraphicsObject::setDescriptors(VulkanDescriptor *vulkanDescriptor)
{
    mDescriptor = vulkanDescriptor;
}

void GraphicsObject::setPipline(VulkanGraphicsPipeline* vulkanPipeline)
{
    mPipeline = vulkanPipeline;
}
void GraphicsObject::setVertexBuffer(VulkanVertexBuffer* vertexBuffer)
{
    mVertexBuffer = vertexBuffer;
}
