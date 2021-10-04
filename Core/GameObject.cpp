#include "GameObject.h"

GameObject::GameObject()
: mTransform(glm::mat4(1.0f))
{
    mGraphicsObject.init(mTransform);
};
GameObject::~GameObject()
{};

glm::mat4 GameObject::getTransform()
{
    return mTransform;
}

GraphicsObject GameObject::getGraphicsObject()
{
    return mGraphicsObject;
}
