#include "Engine.h"
#include <Windows.h>
#include "Scene.h"

float Engine::deltaTime;
POINT Engine::cursorPos;
RECT Engine::clientRect;
bool Engine::lmbPress;
void Engine::update()
{
    lastTimePoint = currentTimePoint;
    currentTimePoint = std::chrono::system_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>
        (currentTimePoint - lastTimePoint).count();
    scene->update();
}

void Engine::paint(HDC targetHDC)
{
    scene->paint(targetHDC);
}


Engine::Engine()
{
    currentTimePoint = std::chrono::system_clock::now();
}
