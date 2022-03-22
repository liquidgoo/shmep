#include "StartGameScript.h"
#include "Engine.h"
#include "GameObject.h"
#include "Scene.h"
#include "setup.h"
void StartGameScript::update()
{
    if (Engine::lmbPress) {
        gameObject->scene->clear();
        mainSceneSetup();
    }
}
