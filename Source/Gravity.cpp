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

    //重力源とActorの距離
    float distance;
    DirectX::XMFLOAT3 d = Mathf::Subtruct(actor_pos, pos);
    distance = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);

    //重力の計算
    float force_magnitude = G * (GetActor()->GetComponent<Movement>()->GetMass() * mass) / (distance * distance);
    DirectX::XMVECTOR Pos= DirectX::XMLoadFloat3(&pos);
    DirectX::XMVECTOR Actor_Pos = DirectX::XMLoadFloat3(&actor_pos);
    //DirectX::XMVECTOR Delta=DirectX::XMVectorSubtract(Actor_Pos, Pos);
    DirectX::XMVECTOR Delta = DirectX::XMVectorSubtract(Pos,Actor_Pos);
    Delta = DirectX::XMVector3Normalize(Delta);
    Delta = DirectX::XMVectorScale(Delta, force_magnitude*speed);

    DirectX::XMStoreFloat3(&force, Delta);
    power = force;
    Movement* movement = GetActor()->GetComponent<Movement>().get();
    //DirectX::XMFLOAT3 acc = movement->GetAcceleration();
    //movement->SetAcceleration(Mathf::Add(force, acc));
    movement->AddForce({ force.x,force.y,force.z });
    AddForce({ force.x,force.y,force.z });

    //速度更新
    if(false)
    {
        assert(mass > 0);
        DirectX::XMStoreFloat3(&acceleration, DirectX::XMVectorScale(DirectX::XMLoadFloat3(&resultant), 1 / mass));
        DirectX::XMStoreFloat3(&velocity, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&velocity), DirectX::XMVectorScale(DirectX::XMLoadFloat3(&acceleration), elapsedTime)));
        DirectX::XMStoreFloat3(&pos, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&pos), DirectX::XMVectorScale(DirectX::XMLoadFloat3(&velocity), elapsedTime)));
        resultant = {};
    }
}

void Gravity::DrawImGui()
{
    ImGui::InputFloat("GravitySpeed", &speed);
    //ImGui::InputFloat("GPMass", &mass);
    //ImGui::InputFloat3("GPPosition", &pos.x);
    //ImGui::InputFloat3("GPVelocity", &velocity.x);
    //ImGui::InputFloat3("GPAcceleration", &acceleration.x);
}

void Gravity::DrawDebug()
{
}

void Gravity::Jump(float power)
{
    Movement* movement = GetActor()->GetComponent<Movement>().get();
    movement->AddForce({ 0,power,0 });
    movement->SetOnGround(false);
}

void Gravity::AddForce(const DirectX::XMFLOAT3& impulse)
{
    resultant.x += impulse.x;
    resultant.y += impulse.y;
    resultant.z += impulse.z;
}
