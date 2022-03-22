#pragma once

#include "fwd/GameObject.fwd.h"
#include "fwd/Camera.fwd.h"
#include <vector>
#include <Windows.h>

class Scene
{
private: 

public:

    std::vector<GameObject*> rootGameObjects;
    std::vector<GameObject*> camObjects;
    void update();
    void paint(HDC targetHDC);
    void clear();

    void addGameObject(GameObject* gameObject);
};

