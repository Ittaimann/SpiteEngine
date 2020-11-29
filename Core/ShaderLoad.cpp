#include "ShaderLoad.h"

const void* ShaderLoad::getData() const
{
    return mData.data();
}

const uint32_t ShaderLoad::getSize() const
{
    return mSize;
}

void ShaderLoad::setData(const std::vector<char>& data)
{
    mData = data;
    mSize = data.size();
}