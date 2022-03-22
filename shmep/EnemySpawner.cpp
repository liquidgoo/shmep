#include "EnemySpawner.h"
#include <numbers>
#include "Vector2.h"
#include "Transform.h"
#include "PlaceholderSprite.h"
#include "EnemyShooterBehaviour.h"
#include "EnemyBomberBehaviour.h"
#include "TimedSelfDestruct.h"
#include "Engine.h"
#include "RectangleCollider.h"
#include "GameObject.h"
#include "Scene.h"
#include "BitmapSprite.h"
void EnemySpawner::spawnBomber()
{
    GameObject* bomber = new GameObject();
    bomber->tag = "Enemy";
    bomber->addComponent(BitmapSprite::getInstance("Assets\\ship2.bmp"));
    bomber->transform->scale = { 0.5,0.5 };

    EnemyBomberBehaviour* behav = new EnemyBomberBehaviour();
    behav->player = player;
    bomber->addComponent(behav);
    float angle = ((float)rand()) / RAND_MAX * PI / 2;
    behav->movingRight = false;
    if (angle > PI / 4)
    {
        angle += PI / 2;
        behav->movingRight = true;
    }
    else {
        behav->movingRight = false;
        bomber->transform->scale.x *= -1;
    }
    Vector2 direction = Vector2(1, 0).rotate(angle);
    bomber->transform->position = player->transform->position + direction * BOMBER_SPAWN_DISTANCE;

    Vector2 size = BitmapSprite::getInstance("Assets\\ship2.bmp")->size/2;
    bomber->addComponent(new RectangleCollider(size));

    gameObject->scene->addGameObject(bomber);

    bomber->addComponent(new TimedSelfDestruct(20000));
}

void EnemySpawner::spawnShooter()
{
    GameObject* shooter = new GameObject();
    shooter->tag = "Enemy";

    float angle = ((float)rand()) / RAND_MAX * PI * 2;
    Vector2 direction = Vector2(1, 0).rotate(angle);
    shooter->transform->position = player->transform->position + direction * BOMBER_SPAWN_DISTANCE;

    shooter->addComponent(BitmapSprite::getInstance("Assets\\ship3.bmp"));
    shooter->transform->scale = { 0.5, 0.5 };

    EnemyShooterBehaviour* behav = new EnemyShooterBehaviour();
    behav->player = player;
    shooter->addComponent(behav);

    Vector2 size = BitmapSprite::getInstance("Assets\\ship3.bmp")->size/2;
    shooter->addComponent(new RectangleCollider(size));

    gameObject->scene->addGameObject(shooter);
}

void EnemySpawner::update()
{
    float scatter;
    if (untilBomberSpawn <= 0) {
        scatter = ((float)rand()) / RAND_MAX * BOMBER_SPAWN_SCATTER;
        untilBomberSpawn = BOMBER_SPAWN_INTERVAL - BOMBER_SPAWN_SCATTER + scatter;
        spawnBomber();
    }
    else {
        untilBomberSpawn -= Engine::deltaTime;
    }

    if (untilShooterSpawn <= 0) {
        scatter = ((float)rand()) / RAND_MAX * SHOOTER_SPAWN_SCATTER;
        untilShooterSpawn = SHOOTER_SPAWN_INTERVAL - SHOOTER_SPAWN_SCATTER + scatter;
        spawnShooter();
    }
    else {
        untilShooterSpawn -= Engine::deltaTime;
    }

}
