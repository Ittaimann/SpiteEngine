#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/mat4x4.hpp>
#include "GraphicsObject.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
    GraphicsObject getGraphicsObject();
    glm::mat4 getTransform();

private:
    glm::mat4 mTransform;
    GraphicsObject mGraphicsObject;
	//Transform mTransform;
};

#endif
