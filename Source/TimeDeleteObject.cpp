#include "TimeDeleteObject.h"

void TimeDeleteObject::Start()
{
}

void TimeDeleteObject::Update(float elapsedTime)
{
    delete_time -= 1.0f * elapsedTime;
    if (delete_time < 0.0f)
    {
        ActorManager::Instance().Remove(GetActor());
    }
}

void TimeDeleteObject::DrawImGui()
{
    ImGui::InputFloat("Time", &delete_time);
}
