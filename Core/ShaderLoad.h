#ifndef SHADER_LOAD_H
#define SHADER_LOAD_H

#include <vector>

enum ShaderStage
{
    VERTEX,
    FRAGMENT
};

// shader data filled in from load.
struct ShaderData
{
    ShaderStage stage;
    size_t unifromInputNum;
    size_t textureInputNum;
    size_t textureSamplerNum;
};

class ShaderLoad
{
public:
    uint32_t getSize() const;
    const void* getData() const;
    void setData(const std::vector<char>& data);
    std::vector<char> compileShader(); 
private:
    std::vector<char> mData;
    uint32_t mSize;
    ShaderData loadedMetaData;
};




#endif
