#pragma once
#include "fwd/SimplePhysics.fwd.h"
#include "Script.h"
class PlayerController : public Script
{
private:
    const float SHOOT_RECHAGE = 100;
    const float PROJECTILE_VELOCITY = 0.075;
    const float BACKFIRE = 0.02;
    float sinceLastShot = 0;
    void shoot();
public:

    SimplePhysics* playerPhysics;
    void update() override;
};

