#include "modelLoad.h"

const std::vector<unsigned char>& ModelLoad::getData()
{
    return mData;
}

void ModelLoad::setData(const std::vector<unsigned char>& data)
{
    mData = data;
    mSize = data.size();
}