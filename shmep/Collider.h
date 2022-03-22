#pragma once
#include "Component.h"
class Collider :
    public Component
{
public:
    virtual bool checkCollision(Collider* other) = 0;
};

