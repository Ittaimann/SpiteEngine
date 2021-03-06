#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include "WindowManager.h"

//TODO: capture all input and set up a way to get what is currently runnning maybe some kind of struct of inputs
//TODO: rethink some of the singleton styling here. Seems like we could probably have this owned by something.
class InputManager
{
public:
    static InputManager *getInputManger();

    void init(WindowManager *manager);
    void cleanup();

    bool getKeyDown(int keyDown);

private:
    static InputManager *InputSingleton;
    WindowManager *mWindow;
};

#endif