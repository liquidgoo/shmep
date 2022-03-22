
#include "Sprite.h"
#include "Transform.h"
#include "Camera.h"
#include "Engine.h"
#include "GameObject.h"

XFORM Sprite::getXFORM(Transform *transform)
{
    XFORM xform1;
    xform1.eM11 = 1;
    xform1.eM12 = 0;
    xform1.eM21 = 0;
    xform1.eM22 = 1;
    xform1.eDx = -size.x/2;
    xform1.eDy = -size.y/2;


    XFORM xform2;
    xform2.eM11 = cos(transform->rotation);
    xform2.eM12 = sin(transform->rotation);
    xform2.eM21 = -sin(transform->rotation);
    xform2.eM22 = cos(transform->rotation);
    xform2.eDx = 0;
    xform2.eDy = 0;

    XFORM result;

    CombineTransform(&result, &xform1, &xform2);
    
    xform1 = result;

    xform2.eM11 = transform->scale.x;
    xform2.eM12 = 0;
    xform2.eM21 = 0;
    xform2.eM22 = -transform->scale.y;
    xform2.eDx = transform->position.x + size.x;
    xform2.eDy = transform->position.y - size.y;
    

    CombineTransform(&result, &xform1, &xform2);
    return result;
}

void Sprite::setXFORM(HDC targetHDC, Camera* cam, Transform *transform)
{
    Transform camWorldTransform;
    GameObject* parent = cam->gameObject;
    while (parent != nullptr) {
        camWorldTransform.position += parent->transform->position;
        parent = parent->parent;
    }

    transform->position.y = -transform->position.y;
    transform->position.x -= camWorldTransform.position.x;
    transform->position.y += camWorldTransform.position.y;
    transform->position.x *= (cam->viewPortRect.w * Engine::clientRect.right) / cam->inGameSize.x;
    transform->position.y *= (cam->viewPortRect.h * Engine::clientRect.bottom) / cam->inGameSize.y;
    transform->position.x += cam->viewPortRect.x;
    transform->position.y += cam->viewPortRect.y;
    transform->position.x += Engine::clientRect.right;
    transform->position.y += Engine::clientRect.bottom *2;
    transform->scale.x *= (cam->viewPortRect.w * Engine::clientRect.right) / cam->inGameSize.x;
    transform->scale.y *= (cam->viewPortRect.h *Engine::clientRect.bottom)/ cam->inGameSize.y;
    xform = getXFORM(transform);
    SetWorldTransform(targetHDC, &xform);
}
