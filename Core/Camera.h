#ifndef CAMERA_H
#define CAMERA_H

#include "WindowManager.h"

class Camera
{
public:
    Camera();
    ~Camera();

    void init();
    void cleanup();
    void update();
    
private:
    //TODO: replace with a proper position struct/transform
    float posX, posY, posZ;
};
#endif