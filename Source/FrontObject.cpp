#include "FrontObject.h"
#include "Movement.h"

#include "Mathf.h"

void FrontObject::Start()
{
    Movement* movement = GetActor()->GetComponent<Movement>().get();
    movement->SetGravity(0.0f);
    movement->SetFriction({ 0.0f });
    movement->SetMoveSpeed(1.0f);
}

void FrontObject::Update(float elapsedTime)
{
    DirectX::XMFLOAT3 nvec = GetActor()->GetComponent<Movement>()->GetVelocity();
    DirectX::XMFLOAT3 impulse;
    //DirectX::XMFLOAT3 ppos = target_actor->GetPosition();
    DirectX::XMVECTOR Object_Position = DirectX::XMLoadFloat3(&GetActor()->GetPosition());
    DirectX::XMVECTOR Trget_Position = DirectX::XMLoadFloat3(&forward);
    //DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Object_Position, Trget_Position);
    DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Trget_Position, Object_Position);
    //Vec = DirectX::XMVector3Normalize(DirectX::XMVectorAdd(Vec, NowVec));
    Vec = DirectX::XMVector3Normalize(Vec);
    DirectX::XMFLOAT3 vec;
    DirectX::XMStoreFloat3(&vec, Vec);

    impulse.x = vec.x * power;
    impulse.y = vec.y * power;
    impulse.z = vec.z * power;

    forward = Mathf::Add(forward, impulse);

    GetActor()->GetComponent<Movement>()->SetVelocity({ 0,0,0 });
    GetActor()->GetComponent<Movement>()->AddImpulse(impulse);
}

void FrontObject::DrawImGui()
{
}

void FrontObject::DrawDebug()
{
}
