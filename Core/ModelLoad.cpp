#include "ModelLoad.h"

const std::vector<unsigned char>& ModelLoad::getData() const
{
    return mData;
}

const uint32_t ModelLoad::getSize() const
{
    return mSize;
}

void ModelLoad::setData(const std::vector<unsigned char>& data)
{
    mData = data;
    mSize = data.size();
}