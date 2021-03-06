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
        mPosZ += 1;
    }
    if(input->getKeyDown(GLFW_KEY_S))
    {
        mPosZ += 1;
    }

    if(input->getKeyDown(GLFW_KEY_A))
    {
        mPosX += 1;
    }

    if(input->getKeyDown(GLFW_KEY_D))
    {
        mPosX -= 1;
    }

}

