#include "Camera.h"
#include "InputManager.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera() {
    mPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera() {}

void Camera::init( const uint32_t& width, const uint32_t& height) {

    mPos = glm::vec3(0.0);
    mView = glm::mat4(1.0);
    mProjection = glm::perspective(glm::radians(45.0f),static_cast<float>(width)/static_cast<float>(height), 0.1f, 100.0f);
    
}

void Camera::cleanup() {}

void Camera::update() {
    InputManager *input = InputManager::getInputManger();
    if (input->getKeyDown(GLFW_KEY_W)) {
       mView = glm::translate(mView, glm::vec3(0.0f,0.0f,1.0f)); 
    }
    if (input->getKeyDown(GLFW_KEY_S)) {
       mView = glm::translate(mView, glm::vec3(0.0f,0.0f,-1.0f)); 
    }
    if (input->getKeyDown(GLFW_KEY_A)) {
       mView = glm::translate(mView, glm::vec3(-1.0f,0.0f,0.0f)); 
    }
    if (input->getKeyDown(GLFW_KEY_D)) {
       mView = glm::translate(mView, glm::vec3(1.0f,0.0f,1.0f)); 
    }
}

glm::vec3 Camera::getPosition() {
    return mPos;
}

glm::mat4 Camera::getView() {
    return mView;
}

glm::mat4 Camera::getProjection() {
    return mProjection;
}
