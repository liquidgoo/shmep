#pragma once

#include "fwd/Component.fwd.h"
#include "fwd/Transform.fwd.h"
#include "fwd/Camera.fwd.h"
#include "fwd/Scene.fwd.h"
#include "fwd/Script.fwd.h"
#include "fwd/Sprite.fwd.h"
#include "fwd/Collider.fwd.h"

#include <string>
#include <vector>
#include <Windows.h>

class GameObject
{
private:
    std::vector<GameObject*> nestedGameObjects;
    std::vector<Component *> components;
public:

    GameObject* parent;
    Scene* scene;
    std::string tag;
    Transform* transform;

    
    void paint(HDC targetHDC, Camera *cam, Transform accumulatedTransform);
    void update();

    void addComponent(Component* component);
    void addChild(GameObject *gameObject);

    Camera* getCamera();
    Sprite* getSprite();
    Collider* getColllider();

    Transform getWorldTransform();

    GameObject();


    ~GameObject();
};

