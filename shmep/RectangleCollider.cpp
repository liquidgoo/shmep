#include "RectangleCollider.h"
#include "Transform.h"
#include "Vector2.h"

bool RectangleCollider::checkCollision(Collider* other)
{
    RectangleCollider* rOther = dynamic_cast<RectangleCollider*>(other);
    if (rOther == nullptr) return false;

    if (transform->position.x + size.x > rOther->transform->position.x &&
        transform->position.x < rOther->transform->position.x + rOther->size.x &&
        transform->position.y + size.y > rOther->transform->position.y &&
        transform->position.y < rOther->transform->position.y + rOther->size.y)
        return true;
    return false;
}

RectangleCollider::RectangleCollider(Vector2 size) : size(size)
{
}
