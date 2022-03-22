#include "PolygonSprite.h"

#include <Windows.h>
#include "Transform.h"


void PolygonSprite::paint(HDC targetHDC, Camera* cam, Transform accumulatedTransform)
{
    setXFORM(targetHDC, cam, &accumulatedTransform);

    HBRUSH prevBrush =(HBRUSH) SelectObject(targetHDC, hBrush);
    
    Polygon(targetHDC, &vertices[0], vertices.size());
    
    SelectObject(targetHDC, prevBrush);
}

PolygonSprite::PolygonSprite(std::vector<POINT> vertices, HBRUSH hBrush):PrimitiveSprite(hBrush)
{
    this->vertices = vertices;
}

