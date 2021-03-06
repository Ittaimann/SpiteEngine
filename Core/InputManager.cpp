#include "InputManager.h"

InputManager *InputManager::InputSingleton = nullptr;

InputManager *InputManager::getInputManger()
{
    if (InputSingleton == nullptr)
    {
        InputSingleton = new InputManager; 
    }
    return InputSingleton;
}
void InputManager::init(WindowManager *manager)
{
    if (InputSingleton != nullptr)
    {
        mWindow = manager;
    }
}
void InputManager::cleanup()
{
    if (InputSingleton != nullptr)
    {
        delete InputSingleton;
        InputSingleton = nullptr;
    }
}

bool InputManager::getKeyDown(int keyDown)
{
    return glfwGetKey(mWindow->getWindow(), keyDown) == GLFW_PRESS;
}