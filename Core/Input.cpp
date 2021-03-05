#include "Input.h"

Input *Input::InputSingleton = nullptr;

Input *Input::getInputManger()
{
    if (InputSingleton != nullptr)
        return InputSingleton;
    //TODO: create the failure case
    return nullptr;
}
void Input::init(WindowManager *manager)
{
    if (InputSingleton == nullptr)
    {
        InputSingleton = new Input();
    }
}
void Input::cleanup()
{
    if (InputSingleton != nullptr)
    {
        delete InputSingleton;
        InputSingleton = nullptr;
    }

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
    }
    // std::cout<<"test"<<std::endl;
}
