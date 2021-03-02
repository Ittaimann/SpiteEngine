#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        std::cout<<"test"<<std::endl;

}


Camera::Camera()
{
}

Camera::~Camera()
{}

void Camera::init(const WindowManager& manager)
{
    glfwSetKeyCallback(manager.getWindow(), key_callback);
}

void Camera::cleanup()
{}

void Camera::update()
{
}

