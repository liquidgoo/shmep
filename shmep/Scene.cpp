#include "Scene.h"
#include "Transform.h"
#include "GameObject.h"

void Scene::update()
{
    for (int i = 0; i < rootGameObjects.size(); i++) {
        rootGameObjects[i]->update();
    }
}

void Scene::paint(HDC targetHDC)
{
    Camera* cam;
    for (GameObject* camObject : camObjects) {
        cam = camObject->getCamera();
        for (GameObject* gameObject : rootGameObjects) {
            if ((unsigned int)gameObject->transform == 0xDDDDDDDD)
            {
                int a = 1;
            }

            gameObject->paint(targetHDC, cam, Transform());
        }
    }
}

void Scene::clear()
{
    while (!rootGameObjects.empty()) {
        delete(rootGameObjects[0]);
    }
    camObjects.resize(0);
}

void Scene::addGameObject(GameObject* gameObject)
{
    rootGameObjects.push_back(gameObject);
    gameObject->scene = this;
}
