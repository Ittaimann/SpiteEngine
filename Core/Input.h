#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class WindowManager;

//TODO: capture all input and set up a way to get what is currently runnning maybe some kind of struct of inputs
//TODO: rename to input manager to more appropriatly show what this is.
//TODO: rethink some of the singleton styling here. Seems like we could probably have this owned by something.
class Input
{
    static Input *InputSingleton;
public:
    static Input *getInputManger();
    static void init(WindowManager* manager);
    static void cleanup();
private:

};

#endif