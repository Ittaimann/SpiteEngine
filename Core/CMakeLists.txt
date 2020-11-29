find_package(glfw3 3.3 REQUIRED)

add_library(
    Core
    WindowManager.cpp
    Loader.cpp
    ModelLoad.cpp
    ShaderLoad.cpp
)

target_link_libraries(Core glfw ${GLFW_LIBRARIES})