#include "Character.h"

#define MAX_UNBEATABLE 2.0f*60

Character::Character()
{
}

void Character::Start()
{
}

void Character::Update(float elapsedTime)
{
    GetActor()->UpdateDelayTime(unbeatable_delay, MAX_UNBEATABLE);
    //RayCast
    {
        //vs_collision->RayCastAxisYUnder();
        GetActor()->GetComponent<VsCollision>()->RayCastAxisXZ();
        GetActor()->GetComponent<VsCollision>()->RayCastAxisY();
        //vs_collision->RayCastAxisXZ();
    }
}

void Character::DrawImGui()
{
}

void Character::DrawDebug()
{
}
