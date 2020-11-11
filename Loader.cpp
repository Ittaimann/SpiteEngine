#include "Loader.h"
#include <assert.h>
#include <iostream>
#include <filesystem>

//Loader: UGH WHAT DO THESE DO, YOU SHOULD PROBABLY LEARN
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include "ThirdParty/tiny_gltf.h"
#include "ThirdParty/json.hpp"


ModelLoad Loader::loadModel(const std::string& file)
{
    std::cout << "Current path is " << std::filesystem::current_path() << std::endl;

    int extensionLoc = file.rfind("."); //Loader: might want a better less failure possible way to do this
    std::string extenstion = file.substr(extensionLoc+1);
    //Loader: definitly going to want to revisit this entire concept. Probably going to need to find a way to map string to enum?
    ModelLoad result;
    if(extenstion == "gltf")
    {
       result = loadGltfModel(file);
    }
    else{
        assert(false && "need to implement other model formats");
    }
  return result ;
}
//Loader: build an error case for this
ModelLoad Loader::loadGltfModel(const std::string& path)
{
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

  if (!res){
    std::cout << "Failed to load glTF: " << path.c_str() << std::endl;
  }
  else{
    std::cout << "Loaded glTF: " << path.c_str() << std::endl;
  }

  ModelLoad result;
  result.setData(TinyModel.buffers[0].data);
  return result;
}