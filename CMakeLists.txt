cmake_minimum_required(VERSION 3.17.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(spite VERSION 0.1)

#TODO: check for more compiler
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-g -Wall -Wextra -pedantic -Werror)
endif()


find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(ThirdParty)
add_subdirectory(VulkanRenderer)
add_subdirectory(Core)
add_executable(spite main.cpp)  
target_link_libraries(spite VulkanDriver Core) 
