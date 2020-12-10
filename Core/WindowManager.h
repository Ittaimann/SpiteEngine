#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include<GLFW/glfw3.h>


class WindowManager
{
public:
    WindowManager();
    ~WindowManager();
    void init(uint32_t width, uint32_t height);
    void cleanup();

    GLFWwindow* getWindow();

    // //could probably pair these
    uint32_t getWidth();
    uint32_t getHeight();
    bool getWindowClosed();
    void pollEvents();
private:
    GLFWwindow* mWindow;
    uint32_t mWidth;
    uint32_t mHeight;

};


#endif