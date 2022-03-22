#pragma once
#include "Script.h"
class EnemySpawner :
    public Script
{
private:
    const float  PI = 3.14159265358979f;

    const float BOMBER_SPAWN_INTERVAL = 2000;
    const float BOMBER_SPAWN_SCATTER = 500;
    const float BOMBER_SPAWN_DISTANCE = 240;
    float untilBomberSpawn = 0;

    const float SHOOTER_SPAWN_INTERVAL = 1500;
    const float SHOOTER_SPAWN_SCATTER = 500;
    const float SHOOTER_SPAWN_DISTANCE = 240;
    float untilShooterSpawn = 0;

    void spawnBomber();
    void spawnShooter();
public:
    GameObject* player;
    void update() override;
};

