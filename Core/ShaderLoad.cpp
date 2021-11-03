#include "ShaderLoad.h"

const void* ShaderLoad::getData() const
{
    return mData.data();
}

uint32_t ShaderLoad::getSize() const
{
    return mSize;
}

void ShaderLoad::setData(const std::vector<char>& data)
{
    mData = data;
    mSize = data.size();
}

//TODO: remove if unused
ShaderData ShaderLoad::getShaderData()
{
    return mLoadedMetaData;
}

//TODO: remove if unused 
void ShaderLoad::initShaderMeta(ShaderStage stage, const std::vector<shaderDescriptor> data)
{
    mLoadedMetaData.stage = stage;
    mLoadedMetaData.mData = data;
}

