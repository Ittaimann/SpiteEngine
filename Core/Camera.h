#ifndef CAMERA_H
#define CAMERA_H

#include "WindowManager.h"
#include "Transform.h"

class Camera
{
public:
    Camera();
    ~Camera();

    void init();
    void cleanup();
    void update();
    glm::vec3 getPosition();    
private:
    //TODO: replace with a proper position struct/transform
//	Transform mTransform;
	glm::vec3 mPos;
};
#endif
