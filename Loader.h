#ifndef LOADER_H
#define LOADER_H

//Loader: define a data format interface for getting and breaking down generic file formats to my own
// for now this can exist as a pseudo loader, and when I'm ready I can build my own format and this will load those
// for now just treat it as a middle man to tinygltf
// For now I should be able to say "loader get ____ data, and it should go to tinygltf and get the appropriate data"
// then when I'm done with it close the file handle and all that.
// what I want back is a constructed model data with maybe some amount of meta data?
// for now just get the raw array of data, and model info.

// TODO: make a generic model class.


#include <string>

class Loader
{
public:
    void loadModel(const std::string& file); //optimize: could probably char* this and remove string in header
private:
    void loadGltfModel(const std::string& path);
};

#endif