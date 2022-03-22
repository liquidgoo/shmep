
#include "PlayerController.h"
#include "Engine.h"
#include "Transform.h"
#include "PlaceholderSprite.h"
#include "SimplePhysics.h"
#include "TimedSelfDestruct.h"
#include "RectangleCollider.h"
#include "GameObject.h"
#include "Scene.h"
#include "BitmapSprite.h"
void PlayerController::shoot()
{
    Vector2 direction = Vector2(1, 0).rotate(transform->rotation);

    GameObject *projectile = new GameObject();
    projectile->tag = "PlayerProjectile";
    projectile->addComponent(BitmapSprite::getInstance("Assets\\bullet1.bmp"));
    projectile->addComponent(new SimplePhysics(direction * PROJECTILE_VELOCITY));
    Vector2 size = BitmapSprite::getInstance("Assets\\bullet1.bmp")->size;
    size.x *= 0.5;
    size.y *= 0.5;
    projectile->addComponent(new RectangleCollider(size));
    projectile->transform->scale = { 0.5, 0.5 };
    projectile->transform->rotation = transform->rotation;
    projectile->transform->position = transform->position + direction * 5 + gameObject->getSprite()->size / 4 - size / 2;
    gameObject->scene->addGameObject(projectile);

    projectile->addComponent(new TimedSelfDestruct(5000));
    playerPhysics->velocity += -direction * BACKFIRE;
}

void PlayerController::update()
{
    Vector2 direction(Engine::cursorPos.x - Engine::clientRect.right/2,
        Engine::clientRect.bottom - Engine::cursorPos.y - Engine::clientRect.bottom/2);
    transform->rotation = direction.getAngle();
    if (Engine::lmbPress && sinceLastShot >= SHOOT_RECHAGE) {
        sinceLastShot = 0;
        shoot();
    }
    else {
        sinceLastShot += Engine::deltaTime;
;    }
}
