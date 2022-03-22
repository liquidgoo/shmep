#pragma once

#include "fwd/Component.fwd.h"

#include "Component.h"
class Script :
    public Component
{
public:
    virtual void update() = 0;
};

