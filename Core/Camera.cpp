#include "Camera.h"
#include "InputManager.h"

Camera::Camera()
{
	mPos = glm::vec3(0.0f,0.0f,0.0f);
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
    	mPos.z += 1.0f;
    }
    if(input->getKeyDown(GLFW_KEY_S))
    {
    	mPos.z -= 1.0f;
    }
    if(input->getKeyDown(GLFW_KEY_A))
    {
    	mPos.x -= 1.0f;
    }
    if(input->getKeyDown(GLFW_KEY_D))
    {
    	mPos.x += 1.0f;
    }

}

glm::vec3 Camera::getPosition()
{
	return mPos;	
}

