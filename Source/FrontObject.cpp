#include "FrontObject.h"
#include "Movement.h"

#include "Mathf.h"

void FrontObject::Start()
{
    Movement* movement = GetActor()->GetComponent<Movement>().get();
    movement->SetFriction({ 0.0f });
    movement->SetTurnSpeed(10.0f);
    movement->SetMoveSpeed(1000.0f);
}

void FrontObject::Update(float elapsedTime)
{
    DirectX::XMFLOAT3 impulse;
    DirectX::XMVECTOR Object_Position = DirectX::XMLoadFloat3(&GetActor()->GetPosition());

    DirectX::XMVECTOR Trget_Position = DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&forward), Object_Position);
    DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Trget_Position, Object_Position);
    Vec = DirectX::XMVector3Normalize(Vec);
    DirectX::XMFLOAT3 vec;
    DirectX::XMStoreFloat3(&vec, Vec);

    impulse.x = vec.x * power;
    impulse.y = vec.y * power;
    impulse.z = vec.z * power;

    forward = Mathf::Add(forward, impulse);

    GetActor()->GetComponent<Movement>()->SetVelocity(impulse);
    GetActor()->GetComponent<Movement>()->Turn(elapsedTime, impulse);
}

void FrontObject::DrawImGui()
{
    ImGui::InputFloat3("Forward", &forward.x);
}

void FrontObject::DrawDebug()
{
    // Tragetデバッグ球描画
    DirectX::XMFLOAT3 position = Mathf::Add(GetActor()->GetPosition(), forward);
    float radius = 2.0f;
    DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
    Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
}
