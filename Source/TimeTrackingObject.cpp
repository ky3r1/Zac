#include "TimeTrackingObject.h"

#include "TrackingObject.h"

void TimeTrackingObject::Start()
{
}

void TimeTrackingObject::Update(float elapsedTime)
{
    if (timer > run_timer)
    {
        GetActor()->GetComponent<TrackingObject>()->Run();
    }
    timer++;
}

void TimeTrackingObject::DrawImGui()
{
    ImGui::Text(u8"SetTimer:%f", run_timer);
    ImGui::InputInt("Timer", &timer);
}

void TimeTrackingObject::DrawDebug()
{
}
