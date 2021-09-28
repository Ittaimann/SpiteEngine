#include "GameObject.h"

GameObject::GameObject()
: mTransform(glm::mat4(1.0f))
{};
GameObject::~GameObject()
{};

glm::mat4 GameObject::getTransform()
{
    return mTransform;
}
