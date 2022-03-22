#pragma once
#include "Script.h"
class TimedSelfDestruct :
    public Script
{
private:
    float timeCount;

public:
    const float TIME_LIMIT;
    void update() override;
    TimedSelfDestruct(float TIME_LIMIT);
};

