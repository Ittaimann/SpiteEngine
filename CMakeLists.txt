cmake_minimum_required(VERSION 3.18.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(spite VERSION 0.1)


find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
#TODO: more robust failure case

include_directories(${PROJECT_SOURCE_DIR})
include_directories(ThirdParty)
add_subdirectory(VulkanRenderer)
add_subdirectory(Core)
add_executable(spite main.cpp)  
#WindowManager.cpp Loader.cpp ModelLoad.cpp ShaderLoad.cpp
target_link_libraries(spite VulkanDriver Core) 