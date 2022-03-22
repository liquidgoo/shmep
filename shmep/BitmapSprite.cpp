#include "BitmapSprite.h"
#include "Camera.h"
#include "Transform.h"
#include "PlaceholderSprite.h"

std::map<std::string, BitmapSprite*> BitmapSprite::instances;

void BitmapSprite::paint(HDC targetHDC, Camera *cam, Transform accumulatedTransform)
{
    if (bitmapLoaded) {
        setXFORM(targetHDC, cam, &accumulatedTransform);
        HDC bitmapHDC = CreateCompatibleDC(targetHDC);
        SelectObject(bitmapHDC, hBitmap);
        TransparentBlt(targetHDC, 0, 0, size.x, size.y, bitmapHDC, 0, 0, size.x, size.y, TRANSPARENT_COLOR);
        DeleteObject(bitmapHDC);
    }
    else {
        PlaceholderSprite::getInstance()->paint(targetHDC, cam, accumulatedTransform);
    }
}

BitmapSprite* BitmapSprite::getInstance(std::string path)
{
    auto instance = instances.find(path);
    if (instance == instances.end()) {
        auto insertResult = instances.insert(std::pair<std::string, BitmapSprite*>(path, new BitmapSprite(path)));
        instance = insertResult.first;
    }
    return (*instance).second;
}

BitmapSprite::BitmapSprite(std::string path)
{
    hBitmap = (HBITMAP)LoadImageA(NULL, (LPCSTR)path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap == NULL) {
        bitmapLoaded = false;
        size = PlaceholderSprite::getInstance()->size;
    }
    else {
        bitmapLoaded = true;
        BITMAP bmp;
        GetObject(hBitmap, sizeof(bmp), &bmp);
        size.x = bmp.bmWidth;
        size.y = bmp.bmHeight;
    }
}

BitmapSprite::~BitmapSprite()
{
    DeleteObject(hBitmap);
}
