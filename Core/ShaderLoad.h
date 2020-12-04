#ifndef SHADER_LOAD_H
#define SHADER_LOAD_H

#include <vector>
class ShaderLoad
{
public:
    const uint32_t getSize() const;
    const void* getData() const;
    void setData(const std::vector<char>& data);
    std::vector<char> compileShader(); 
private:
    std::vector<char> mData;
    uint32_t mSize;
};


#endif