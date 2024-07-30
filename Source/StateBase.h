#pragma once
#include "Actor.h"
class StateBase
{
public:
    virtual void Start(float elapsedTime,Actor** actor) {};
    virtual void Update(float elapsedTime) {};
    virtual void End(float elapsedTime) {};
};