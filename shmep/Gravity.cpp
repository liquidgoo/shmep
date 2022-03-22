#include "Gravity.h"
#include "Engine.h"
#include "SimplePhysics.h"
void Gravity::update()
{
    physics->velocity.y -= G * Engine::deltaTime;
}
