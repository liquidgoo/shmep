#pragma once

#include "fwd/Sprite.fwd.h"

#include "Sprite.h"
class PrimitiveSprite :
    public Sprite
{
protected:
    HBRUSH hBrush;
public:
    PrimitiveSprite(HBRUSH hBrush);
    ~PrimitiveSprite();
};

