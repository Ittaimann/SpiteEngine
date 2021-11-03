#ifndef SHADER_LOAD_H
#define SHADER_LOAD_H

#include <vector>
#include <string>

enum class ShaderStage : uint8_t {
    VERTEX,
    FRAGMENT
};

//inherit from uint just to make taking input a bit easier
enum class ShaderDataType : uint8_t{
    BUFFER,
    TEXTURE,
    SAMPLER
};

struct shaderDescriptor {
    ShaderDataType mType;
    uint32_t mBindingLocation;
    uint32_t mSetLocation; //unused for now thanks vulkan
    uint32_t mSize;        //for buffer type
    std::string mName;
};
// shader data filled in from load.
struct ShaderData {
    ShaderStage stage;
    //Gross more vector. honestly my code would be way faster
    //if I just... made my own containers or just did c style
    //arrays at this point
    std::vector<shaderDescriptor> mData;
};

class ShaderLoad {
  public:
    uint32_t getSize() const;
    const void *getData() const;
    void setData(const std::vector<char> &data);
    std::vector<char> compileShader();
    ShaderData getShaderData();
    void initShaderMeta(ShaderStage stage);
    void initShaderMeta(ShaderStage stage, const std::vector<shaderDescriptor> data);

  private:
    std::vector<char> mData;
    uint32_t mSize;
    ShaderData mLoadedMetaData;
};

#endif
