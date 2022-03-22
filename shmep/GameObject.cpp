#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Script.h"
#include "Camera.h"
#include "PlaceholderSprite.h"
#include "BitmapSprite.h"
#include "Scene.h"
#include "Collider.h"


void GameObject::paint(HDC targetHDC, Camera *cam, Transform accumulatedTransform)
{
    
    accumulatedTransform.position += transform->position;
    accumulatedTransform.scale.x *= transform->scale.x;
    accumulatedTransform.scale.y *= transform->scale.y;
    accumulatedTransform.rotation += transform->rotation;

    Sprite* sprite = getSprite();
    if (sprite != nullptr) sprite->paint(targetHDC, cam, accumulatedTransform);

    for (GameObject* nestedGameObject : nestedGameObjects) {
        nestedGameObject->paint(targetHDC, cam, accumulatedTransform);
    }
}

void GameObject::update()
{
    Script* script;
    for (int i = 0; i < components.size(); i++) {
        script = dynamic_cast<Script*> (components[i]);
        if (script != nullptr) {
            script->update();
        }
    }
    for (GameObject* nestedGameObject : nestedGameObjects) {
        nestedGameObject->update();
    }
}

void GameObject::addComponent(Component* component)
{
        components.push_back(component);
        component->gameObject = this;
        component->transform = transform;
}

void GameObject::addChild(GameObject *gameObject)
{
    nestedGameObjects.push_back(gameObject);
    gameObject->parent = this;
    gameObject->scene = scene;
}

Camera* GameObject::getCamera()
{
    Camera* cam;
    for (Component* component : components) {
        cam = dynamic_cast<Camera*> (component);
        if (cam != nullptr) {
            return cam;
        }
    }
    return nullptr;
}

Sprite* GameObject::getSprite()
{
    Sprite* sprite;
    for (Component* component : components) {
        sprite = dynamic_cast<Sprite*> (component);
        if (sprite != nullptr) {
            return sprite;
        }
    }
    return nullptr;
}

Collider* GameObject::getColllider()
{
    Collider* collider;
    for (Component* component : components) {
        collider = dynamic_cast<Collider*> (component);
        if (collider != nullptr) {
            return collider;
        }
    }
    return nullptr;
}

Transform GameObject::getWorldTransform()
{
    Transform t = *transform;
    GameObject* parent = this->parent;
    while (parent != nullptr) {
        t.position += parent->transform->position;
        t.scale.x *= parent->transform->scale.x;
        t.scale.y *= parent->transform->scale.y;
        t.rotation += parent->transform->rotation;
        parent = parent->parent;
    }
    return t;
}

GameObject::GameObject() {
    transform = new Transform();
    components.push_back(transform);
    parent = nullptr;
}

GameObject::~GameObject()
{

    while (!nestedGameObjects.empty()) {
        delete(nestedGameObjects[0]);
    }
   
    while (!components.empty()) {
        if (dynamic_cast<PlaceholderSprite*>(components[0]) == nullptr &&
            dynamic_cast<BitmapSprite*>(components[0]) == nullptr) {

            delete(components[0]);
        }
        components.erase(components.begin());
    }
    auto parentGameObjects = (parent == nullptr) ? &scene->rootGameObjects : &parent->nestedGameObjects;
    auto iter = parentGameObjects->begin();
    while (*iter != this) {
        iter++;
    }
    parentGameObjects->erase(iter);
}
