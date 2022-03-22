#include "PlaceholderSprite.h"

PlaceholderSprite* PlaceholderSprite::instance;

PlaceholderSprite* PlaceholderSprite::getInstance()
{
    if (instance == nullptr) {
        instance = new PlaceholderSprite();
    }
    return instance;
}

PlaceholderSprite::PlaceholderSprite():PolygonSprite(createVertices(), createBrush()) {
    size.x = TRIANGLE_X;
    size.y = TRIANGLE_Y;
}

std::vector<POINT> PlaceholderSprite::createVertices()
{
    std::vector<POINT> vertices;
    POINT p = { 0, TRIANGLE_Y };
    vertices.push_back(p);
    p = { 0, 0 };
    vertices.push_back(p);
    p = { TRIANGLE_X, TRIANGLE_Y/2 };
    vertices.push_back(p);
    return vertices;
}

HBRUSH PlaceholderSprite::createBrush()
{
    return CreateSolidBrush(BRUSH_COLOR);
}
