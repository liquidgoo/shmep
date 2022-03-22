#pragma once

#include "fwd/PolygonSprite.fwd.h"
#include <Windows.h>
#include <vector>

#include "PolygonSprite.h"

#define TRIANGLE_X 10
#define TRIANGLE_Y 6
#define BRUSH_COLOR RGB(255, 0 ,0)
class PlaceholderSprite :
    public PolygonSprite
{
private:
    static PlaceholderSprite* instance;
    PlaceholderSprite();
    std::vector<POINT> createVertices();
    HBRUSH createBrush();
public:
    PlaceholderSprite(PlaceholderSprite& other) = delete;
    void operator=(const PlaceholderSprite&) = delete;

    static PlaceholderSprite* getInstance();
};

