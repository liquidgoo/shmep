#pragma once
#include "Script.h"
class EnemyBomberBehaviour :
    public Script
{
private:
    void bomb();
    const float BOMB_RECHAGE = 600;
    const float PROJECTILE_VELOCITY = 0.025;
    const float TARGET_DISTANCE = 75;
    const float REST_DISTANCE = 15;
    const float BOMBING_ANGLE = 0.52;
    const float BOMB_ANGLE = 0.087;
    const float HOR_VELOCITY = 0.05;
    const float VER_VELOCITY = 0.025;
    const float PROJECTILE_LIFE_TIME = 20000;
    float sinceLastBomb = 0;
public:
    bool movingRight;
    GameObject* player;

    void update() override;

};

