#pragma once
#include "Script.h"
#include "Vector2.h"
class SimplePhysics :
    public Script
{
public:
    Vector2 velocity;

    void update() override;

    SimplePhysics();
    SimplePhysics(float xVelocity,float yVelocity);
    SimplePhysics(Vector2 velocity);
};

