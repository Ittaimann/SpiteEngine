#ifndef CAMERA_H
#define CAMERA_H

#include "WindowManager.h"

class Camera
{
public:
    Camera();
    ~Camera();

    void init(const WindowManager& window);
    void cleanup();
    void update();
    
    //REFACTOR: create a proper input singleton
    //void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


private:
    //TODO: replace with a proper position struct/transform
    float posX, posY, posZ;
};
#endif