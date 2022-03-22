#include "EnemyBomberBehaviour.h"
#include "Transform.h"
#include "Engine.h"
#include "PlaceholderSprite.h"
#include "SimplePhysics.h"
#include "TimedSelfDestruct.h"
#include "RectangleCollider.h"
#include "GameObject.h"
#include "Scene.h"
#include "BitmapSprite.h"

void EnemyBomberBehaviour::bomb()
{
    Vector2 direction = Vector2(0, -1).rotate(BOMB_ANGLE * (movingRight? 1: -1));

    GameObject* projectile = new GameObject();
    projectile->tag = "EnemyProjectile";
    projectile->addComponent(BitmapSprite::getInstance("Assets\\bomb.bmp"));
    projectile->addComponent(new SimplePhysics(direction * PROJECTILE_VELOCITY));
    projectile->transform->scale = { 0.5, 0.5 };

    Vector2 size = BitmapSprite::getInstance("Assets\\bomb.bmp")->size;
    size.x *= 0.5;
    size.y *= 0.5;
    projectile->addComponent(new RectangleCollider(size));
    float angle = -acosf(direction.x);

    projectile->transform->rotation = angle;
    projectile->transform->position = transform->position + direction * 5 + gameObject->getSprite()->size / 4 - size / 2;
    gameObject->scene->addGameObject(projectile);

    projectile->addComponent(new TimedSelfDestruct(PROJECTILE_LIFE_TIME));
}

void EnemyBomberBehaviour::update()
{
    
    transform->position.x += (movingRight ? 1 : -1) * HOR_VELOCITY * Engine::deltaTime;

    float targetHeight = player->transform->position.y + TARGET_DISTANCE;

    if (abs(targetHeight - transform->position.y) > REST_DISTANCE) {
        transform->position.y += (targetHeight > transform->position.y ? 1 : -1) * VER_VELOCITY * Engine::deltaTime;
    }

    if (acosf((transform->position - player->transform->position).norm().y) <= BOMBING_ANGLE
        && sinceLastBomb >= BOMB_RECHAGE) {
        sinceLastBomb = 0;
        bomb();
    }
    else {
        sinceLastBomb += Engine::deltaTime;
    }
}
