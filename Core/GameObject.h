#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/mat4x4.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();
    glm::mat4 getTransform();

private:
    glm::mat4 mTransform;
	//Transform mTransform;
};

#endif
