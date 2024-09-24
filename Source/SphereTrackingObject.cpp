#include "SphereTrackingObject.h"
#include "TrackingObject.h"
#include "CollisionObject.h"
#include "Mathf.h"

SphereTrackingObject::SphereTrackingObject()
{
}

SphereTrackingObject::~SphereTrackingObject()
{
}

void SphereTrackingObject::Start()
{
    GetActor()->GetComponent<TrackingObject>()->SetSphereRadius(FLT_MAX);
}

void SphereTrackingObject::Update(float elapsedTime)
{
    Actor* target_actor = GetActor()->GetComponent<CollisionObject>()->GetTargetActor();
    if (target_actor != nullptr)
    {
        if (Mathf::Distance(GetActor()->GetPosition(), target_actor->GetPosition()) < radius_search)
        {
            GetActor()->GetComponent<TrackingObject>()->SetRunObject(true);
        }
    }
}

void SphereTrackingObject::DrawImGui()
{
}

void SphereTrackingObject::DrawDebug()
{
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.4, 0.2, 0.7, 1);
        Graphics::Instance().GetDebugRenderer()->DrawSphere(GetActor()->GetPosition(), radius_search, color);
    }
}
