find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
add_library(
    Core
    WindowManager.cpp
    Loader.cpp
    ModelLoad.cpp
    ShaderLoad.cpp
    Camera.cpp
    InputManager.cpp
    GameObject.cpp
    GraphicsObject.cpp
)

target_link_libraries(Core glfw ${GLFW_LIBRARIES})
