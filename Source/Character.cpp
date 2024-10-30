#include "Character.h"
#include "VsCollision.h"

#define MAX_UNBEATABLE 2.0f*60

Character::Character()
{
}

void Character::Start()
{
}

void Character::Update(float elapsedTime)
{

    GetActor()->GetModel()->SetHitStopAnimationSpeed(GetActor()->GetAnimationSpeed());
    //–³“GŽžŠÔXV
    GetActor()->UpdateDelayTime(unbeatable_delay, MAX_UNBEATABLE);
    //RayCast
    GetActor()->SetRayPosition(GetActor()->GetPosition());
    if(true)
    {
        GetActor()->GetComponent<VsCollision>()->RayCastAxisYUnder();
        GetActor()->GetComponent<VsCollision>()->RayCastAxisXZ();
        //GetActor()->GetComponent<VsCollision>()->RayCastAxisYUp();
        //GetActor()->GetComponent<VsCollision>()->RayCastAxisYUnder();
        //if (GetActor()->GetPosition().y < 0.0f)
        //{
        //    GetActor()->SetPosition({ GetActor()->GetPosition().x, 0.0f, GetActor()->GetPosition().z });
        //}
    }
    else
    {
        if (GetActor()->GetPosition().y < 0.0f)
        {
            GetActor()->SetPosition({ GetActor()->GetPosition().x, 0.0f, GetActor()->GetPosition().z });
        }
    }
}

void Character::DrawImGui()
{
    ImGui::SliderFloat("health", &current_health, 0.0f, max_health);
}

void Character::DrawDebug()
{
}

void Character::TakeDamage(float damage)
{
    current_health -= damage;
}

void Character::TakeHeel(float heel)
{
    current_health += heel;
}
