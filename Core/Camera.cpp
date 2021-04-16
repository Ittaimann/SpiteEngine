#include "Camera.h"
#include "InputManager.h"

Camera::Camera()
{
}

Camera::~Camera()
{}

void Camera::init()
{
}

void Camera::cleanup()
{}
void Camera::update()
{
    InputManager* input = InputManager::getInputManger();
    if(input->getKeyDown(GLFW_KEY_W))
    {
    	mTransform.PosZ += 1;
    }
    if(input->getKeyDown(GLFW_KEY_S))
    {
    	mTransform.PosZ -= 1;
    }

    if(input->getKeyDown(GLFW_KEY_A))
    {
    	mTransform.PosX += 1;
    }

    if(input->getKeyDown(GLFW_KEY_D))
    {
    	mTransform.PosX += 1;
    }

}

