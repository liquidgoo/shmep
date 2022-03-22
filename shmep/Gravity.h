#pragma once
#include "fwd/SimplePhysics.fwd.h"
#include "Script.h"
class Gravity :
    public Script
{
private:
    const float G = 0.00002;
public:
    SimplePhysics* physics;
    void update() override;
};

