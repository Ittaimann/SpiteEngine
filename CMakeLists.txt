cmake_minimum_required(VERSION 3.18.2)
project(spite VERSION 0.1)


find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
#TODO: more robust failure case
add_executable(spite main.cpp)  

target_link_libraries(spite glfw ${GLFW_LIBRARIES} Vulkan::Vulkan)