#include "TimedSelfDestruct.h"
#include "Engine.h"
#include "GameObject.h"
void TimedSelfDestruct::update()
{
    timeCount += Engine::deltaTime;
    if (timeCount > TIME_LIMIT)
        delete(gameObject);
}

TimedSelfDestruct::TimedSelfDestruct(float TIME_LIMIT) : TIME_LIMIT(TIME_LIMIT)
{
    timeCount = 0;
}
