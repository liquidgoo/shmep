#include "SimplePhysics.h"
#include "Engine.h"
#include "Transform.h"

void SimplePhysics::update()
{
    transform->position += velocity * Engine::deltaTime;
}

SimplePhysics::SimplePhysics()
{
    velocity = { 0,0 };
}

SimplePhysics::SimplePhysics(float xVelocity, float yVelocity)
{
    velocity.x = xVelocity;
    velocity.y = yVelocity;
}

SimplePhysics::SimplePhysics(Vector2 velocity)
{
    this->velocity = velocity;
}
