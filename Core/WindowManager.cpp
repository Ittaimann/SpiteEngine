#include "WindowManager.h"

WindowManager::WindowManager()
{}
WindowManager::~WindowManager()
{}

void WindowManager::init(const uint32_t width, const uint32_t height)
{
    mWidth = width;
    mHeight = height;
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    mWindow = glfwCreateWindow(mWidth, mHeight, "Spite", nullptr, nullptr);
    glfwSetWindowUserPointer(mWindow, this);

}
void WindowManager::cleanup()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate(); // maybe mose this else where?
}

GLFWwindow* WindowManager::getWindow() const
{
    return mWindow;
}

uint32_t WindowManager::getWidth() const
{
    return mWidth;
}

uint32_t WindowManager::getHeight() const
{
    return mHeight;
}

bool WindowManager::getWindowClosed()
{
	return !glfwWindowShouldClose(mWindow);
}
void WindowManager::pollEvents()
{
	glfwPollEvents();
}
