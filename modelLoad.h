#ifndef MODEL_LOAD_H
#define MODEL_LOAD_H

#include <cstdint>
#include <vector>


//TODO: Need to figure out if this is just going to be to be for loading or is this
// going to be the proper model class.
class ModelLoad
{

public:
    const std::vector<unsigned char>& getData() const;
    const uint32_t getSize() const;
    void setData(const std::vector<unsigned char>& data);
private:
    std::vector<unsigned char> mData;
    uint32_t mSize;
};

#endif