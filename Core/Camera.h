#ifndef CAMERA_H
#define CAMERA_H

#include "WindowManager.h"
#include "glm/glm.hpp"

class Camera {
  public:
    Camera();
    ~Camera();

    void init(const uint32_t &width, const uint32_t &height);
    void cleanup();
    void update();
    glm::vec3 getPosition();
    glm::mat4 getView();
    glm::mat4 getProjection();

  private:
    //TODO: replace with a proper position struct/transform
    glm::vec3 mPos;
    glm::mat4 mView;
    glm::mat4 mProjection;
};
#endif
