
#include "Loader.h"

#include <assert.h>
#include <filesystem>
#include <iostream>

// KNOWLEDGE: UGH WHAT DO THESE DO, YOU SHOULD PROBABLY LEARN
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include "ThirdParty/json.hpp"
#include "ThirdParty/tiny_gltf.h"

ModelLoad Loader::loadModel(const std::string &file) {
    std::cout << "Current path is " << std::filesystem::current_path()
              << std::endl;

    int extensionLoc = file.rfind(
        "."); // TODO: might want a better less failure possible way to do this
    std::string extenstion = file.substr(extensionLoc + 1);
    // TODO: definitly going to want to revisit this entire concept. Probably
    // going to need to find a way to map string to enum?
    ModelLoad result;
    if (extenstion == "gltf") {
        result = loadGltfModel(file);
    } else {
        assert(false && "need to implement other model formats");
    }
    return result;
}
// TODO: build an error case for this
ModelLoad Loader::loadGltfModel(const std::string &path) {
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;
    tinygltf::Model TinyModel;
    bool res = loader.LoadASCIIFromFile(&TinyModel, &err, &warn, path.c_str());
    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cout << "ERR: " << err << std::endl;
    }

    if (!res) {
        std::cout << "Failed to load glTF: " << path.c_str() << std::endl;
    } else {
        std::cout << "Loaded glTF: " << path.c_str() << std::endl;
    }

    ModelLoad result;
    result.setData(TinyModel.buffers[0].data);
    return result;
}

std::vector<ShaderLoad> Loader::loadShader(const std::string &path) {
    //TODO: consume shader meta file here and build it out

    std::vector<ShaderLoad> result;
    //std::vector<char> Buffer = readFile(path);

    std::ifstream file(path); //, std::ios::ate | std::ios::binary);
    json j;
    file >> j;
    std::cout << j["_comment"] << std::endl;
    auto stages = j["stages"];
    for (auto stage : stages) {
        ShaderLoad &newShader = result.emplace_back();
        //TODO: don't do this
        std::string assetCache = "AssetCache/";
        assetCache += stage["file"];
        std::vector<char> shaderBinary = readFile(assetCache);
        newShader.setData(shaderBinary);
        ShaderStage shaderStage = (ShaderStage)stage["stage"];
        auto inputs = stage["inputs"];
        std::vector<shaderDescriptor> descriptors;
        for (auto descriptor : inputs) {
            shaderDescriptor &newDescriptor = descriptors.emplace_back();
            newDescriptor.mBindingLocation = descriptor["binding"];
            newDescriptor.mSetLocation = 0; // temp 0
            newDescriptor.mSize = descriptor["size"];
            newDescriptor.mType = (ShaderDataType)determineDescriptorType(descriptor["type"]); // need to do the string convert... UGH
        }
        newShader.initShaderMeta(shaderStage, descriptors);
    }
    return result;
}

std::vector<char> Loader::readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

//TODO: rethink this. Its just a silly way of doing it
uint8_t Loader::determineDescriptorType(const std::string &type) {
    if (type == "buffer") {
        return 0;
    } else {
        assert(false);
        return 0;
    }
}
