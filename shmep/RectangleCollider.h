#pragma once
#include "Collider.h"
#include "Rect.h"
#include "Vector2.h"
class RectangleCollider :
    public Collider
{
public:
    Vector2 size;
    bool checkCollision(Collider* other) override;
    RectangleCollider(Vector2 size);
};

