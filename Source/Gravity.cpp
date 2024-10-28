#include "Gravity.h"
#include "Mathf.h"
#include "Movement.h"

void Gravity::Start()
{
}

void Gravity::Update(float elapsedTime)
{
    DirectX::XMFLOAT3 force = {};
    DirectX::XMFLOAT3 actor_pos = GetActor()->GetPosition();
    //万有引力定数
    float G = 6.67430e-11f;

    //重力限とActorの距離
    float distance;
    DirectX::XMFLOAT3 d = Mathf::Subtruct(actor_pos, pos);
    distance = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);

    //重力の計算
    float force_magnitude = G * (GetActor()->GetComponent<Movement>()->GetMass() * mass) / (distance * distance);
    DirectX::XMVECTOR Pos= DirectX::XMLoadFloat3(&pos);
    DirectX::XMVECTOR Actor_Pos = DirectX::XMLoadFloat3(&actor_pos);
    DirectX::XMVECTOR Delta=DirectX::XMVectorSubtract(Pos, Actor_Pos);
    Delta = DirectX::XMVector3Normalize(Delta);
    Delta = DirectX::XMVectorScale(Delta, force_magnitude);

    DirectX::XMStoreFloat3(&force, Delta);
    GetActor()->GetComponent<Movement>()->AddForce(force);
}

void Gravity::DrawImGui()
{
}

void Gravity::DrawDebug()
{
}
