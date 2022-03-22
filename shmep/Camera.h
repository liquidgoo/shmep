#pragma once

#include "fwd/Component.fwd.h"
#include "fwd/Rect.fwd.h"
#include "fwd/Vector2.fwd.h"

#include "Vector2.h"
#include "Rect.h"
#include "Component.h"
class Camera :
    public Component
{
public:
    Vector2 inGameSize;
    Rect viewPortRect;
};

