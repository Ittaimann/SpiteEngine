#ifndef SHADER_LOAD_H
#define SHADER_LOAD_H

#include <vector>

enum ShaderStage {
    VERTEX,
    FRAGMENT
};

enum ShaderDataType {
    BUFFER,
    TEXTURE,
    SAMPLER
};

struct shaderDescriptor {
    ShaderDataType mType;
    uint32_t mBindingLocation;
    uint32_t mSetLocation; //unused for now thanks vulkan
    uint32_t mSize;        //for buffer type
};
// shader data filled in from load.
struct ShaderData {
    ShaderStage stage;
    std::vector<shaderDescriptor> mData;
    //wanted to do some c style stuff but decided against it
    //shaderDescriptor* mData; // array of shader data... kinda annoying but fair
    //uint32_t descriptorCount;
    // void cleanup()
    //{
    //  delete mData;
    //}
};

class ShaderLoad {
  public:
    uint32_t getSize() const;
    const void *getData() const;
    void setData(const std::vector<char> &data);
    std::vector<char> compileShader();
    ShaderData getShaderData();

  private:
    std::vector<char> mData;
    uint32_t mSize;
    ShaderData mLoadedMetaData;
};

#endif
