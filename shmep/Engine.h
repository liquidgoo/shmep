#pragma once

#include "fwd/Scene.fwd.h"

#include <chrono>
#include <Windows.h>
class Engine
{
private:
    std::chrono::time_point<std::chrono::system_clock> lastTimePoint,
        currentTimePoint;

public:
    static float deltaTime;

    static POINT cursorPos;
    static RECT clientRect;
    static bool lmbPress;

    Scene* scene;

    void update();
    void paint(HDC targetHDC);
    Engine();
};

