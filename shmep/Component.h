#pragma once

#include "fwd/GameObject.fwd.h"
#include "fwd/Transform.fwd.h"

#include <string>
#include <Windows.h>



class Component
{
public:
    GameObject* gameObject;
    Transform* transform;
    std::string tag;

    virtual ~Component();
};

