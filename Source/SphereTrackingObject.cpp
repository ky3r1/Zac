#include "SphereTrackingObject.h"
#include "Mathf.h"

SphereTrackingObject::SphereTrackingObject()
{
}

SphereTrackingObject::~SphereTrackingObject()
{
}

void SphereTrackingObject::Start()
{
    TrackingObject::Start();
    c_sphere.radius = FLT_MAX;
}

void SphereTrackingObject::Update(float elapsedTime)
{
    TrackingObject::Update(elapsedTime);
    if (target_actor != nullptr)
    {
        if (Mathf::Distance(GetActor()->GetPosition(), target_actor->GetPosition()) < radius_search)
        {
            run_obj = true;
        }
    }
}

void SphereTrackingObject::DrawImGui()
{
    TrackingObject::DrawImGui();
}

void SphereTrackingObject::DrawDebug()
{
    TrackingObject::DrawDebug();
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.4, 0.2, 0.7, 1);
        Graphics::Instance().GetDebugRenderer()->DrawSphere(GetActor()->GetPosition(), radius_search, color);
    }
}
