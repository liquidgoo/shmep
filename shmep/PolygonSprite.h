#pragma once

#include "fwd/PrimitiveSprite.fwd.h"
#include "fwd/Camera.fwd.h"
#include "fwd/Transform.fwd.h"

#include "PrimitiveSprite.h"
#include <vector>

class PolygonSprite :
    public PrimitiveSprite
{
private:
    std::vector<POINT> vertices;
public:
    void paint(HDC targetHDC, Camera *cam, Transform accumulatedTransform) override;
    PolygonSprite(std::vector<POINT> vertices, HBRUSH hBrush);
    
};

