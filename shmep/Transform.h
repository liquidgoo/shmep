#pragma once

#include "fwd/Component.fwd.h"
#include "fwd/Vector2.fwd.h"
#include "Component.h"
#include "Vector2.h"
class Transform :
    public Component
{
public: 
    Vector2 position;
    Vector2 scale;
    float rotation;

    Transform();
};

