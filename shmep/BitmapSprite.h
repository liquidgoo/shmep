#pragma once


#include "fwd/Sprite.fwd.h"
#include "fwd/Camera.fwd.h"
#include "fwd/Transform.fwd.h"
#include "fwd/PlaceholderSprite.fwd.h"

#include <map>

#include "Sprite.h"
#define TRANSPARENT_COLOR RGB(255,255,255)
class BitmapSprite :
    public Sprite
{
private:
    static std::map<std::string, BitmapSprite*> instances;
    HBITMAP hBitmap;
    bool bitmapLoaded;
    BitmapSprite(std::string path);
public:
    void paint(HDC targetHDC, Camera *cam, Transform accumulatedTransform) override;
    static BitmapSprite* getInstance(std::string path);
    ~BitmapSprite();
};

