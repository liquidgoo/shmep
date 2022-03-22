#pragma once

#include "fwd/Component.fwd.h"
#include "fwd/Camera.fwd.h"
#include "fwd/Transform.fwd.h"
#include "Component.h"
#include "Vector2.h"

class Sprite :
    public Component
{
private:
    XFORM xform;
    XFORM getXFORM(Transform *transform);

protected:
    void setXFORM(HDC targetHDC, Camera* cam, Transform* transform);
public:

    Vector2 size;
    virtual void paint(HDC targetHDC, Camera *cam, Transform accumulatedTransform) = 0;
};

