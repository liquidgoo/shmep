#include "PrimitiveSprite.h"

PrimitiveSprite::PrimitiveSprite(HBRUSH hBrush)
{
    this->hBrush = hBrush;
}

PrimitiveSprite::~PrimitiveSprite()
{
    DeleteObject(hBrush);
}
