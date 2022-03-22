#include "EnemyShooterBehaviour.h"
#include "Transform.h"
#include "Engine.h"
#include "PlaceholderSprite.h"
#include "SimplePhysics.h"
#include "TimedSelfDestruct.h"
#include "RectangleCollider.h"
#include "GameObject.h"
#include "Scene.h"
#include "BitmapSprite.h"
void EnemyShooterBehaviour::shoot()
{
    float scatterAngle = ((float)rand()) / RAND_MAX * SCATTER - SCATTER / 2;
    Vector2 direction = (player->transform->position - transform->position).norm().rotate(scatterAngle);

    GameObject* projectile = new GameObject();
    projectile->tag = "EnemyProjectile";
    projectile->addComponent(BitmapSprite::getInstance("Assets\\bullet2.bmp"));
    projectile->addComponent(new SimplePhysics(direction * PROJECTILE_VELOCITY));
    projectile->transform->scale = { 0.5, 0.5 };

    Vector2 size = BitmapSprite::getInstance("Assets\\bullet2.bmp")->size;
    size.x *= 0.5;
    size.y *= 0.5;
    projectile->addComponent(new RectangleCollider(size));

    
    projectile->transform->rotation = direction.getAngle();
    projectile->transform->position = transform->position + direction * 2  +gameObject->getSprite()->size / 4 - size / 2;
    gameObject->scene->addGameObject(projectile);

    projectile->addComponent(new TimedSelfDestruct(PROJECTILE_LIFE_TIME));
}
void EnemyShooterBehaviour::update()
{
    Vector2 direction = (player->transform->position - transform->position).norm();
    transform->rotation = direction.getAngle();

    Vector2 targetPoint = player->transform->position - direction * TARGET_DISTANCE;
    
    if ((targetPoint - transform->position).abs() > REST_DISTANCE) {
        direction = (targetPoint - transform->position).norm();
        transform->position += direction * VELOCITY * Engine::deltaTime;
    }

    if ((player->transform->position - transform->position).abs() <= SHOOTING_RANGE
        && sinceLastShot >= SHOOT_RECHAGE) {
        sinceLastShot = 0;
        shoot();
    }
    else {
        sinceLastShot += Engine::deltaTime;
    }
}
