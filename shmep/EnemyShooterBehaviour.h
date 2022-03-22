#pragma once
#include "Script.h"
class EnemyShooterBehaviour :
    public Script
{

private:
    void shoot();
    const float SHOOT_RECHAGE = 650;
    const float PROJECTILE_VELOCITY = 0.05;
    const float SCATTER = 0.35;
    const float TARGET_DISTANCE = 50;
    const float REST_DISTANCE = 10;
    const float SHOOTING_RANGE = 75;
    const float VELOCITY = 0.03;
    const float PROJECTILE_LIFE_TIME = 10000;
    float sinceLastShot = 0;
public:
    GameObject* player;

    void update() override;

};

