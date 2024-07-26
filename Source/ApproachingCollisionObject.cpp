#include "ApproachingCollisionObject.h"
#include "Movement.h"
#include "VsCollision.h"
#include "Mathf.h"

ApproachingCollisionObject::ApproachingCollisionObject()
{

}

ApproachingCollisionObject::~ApproachingCollisionObject()
{
}

void ApproachingCollisionObject::Start()
{
    default_position = GetActor()->GetPosition();
    Movement* movement = GetActor()->GetComponent<Movement>().get();
    movement->SetGravity(0.0f);
    movement->SetFriction({ 0.0f,0.0f,0.0f });
}

void ApproachingCollisionObject::Update(float elapsedTime)
{
    Actor* player = nullptr;
    
    if (GetActor()->GetComponent<VsCollision>()->SphereVsSphere(ActorType::Player, &player))
    {
        // 体力を1回復
        if (!test_flg)
        {
            player->SetHealth(player->GetHealth() + 1.0f);
            test_flg = true;
        }
        GetActor()->SetDeadFlag(true);
    }
    {
        DirectX::XMFLOAT4 rotation = GetActor()->GetRotation();
        float rot = 0.1f / 3.14f;
        GetActor()->SetRotation({ rotation.x + rot, rotation.y, rotation.z + rot, rotation.w });
        if (rotation.x > 3.14f)GetActor()->SetRotation({ -3.14f, rotation.y, rotation.z, rotation.w });
        if (rotation.y > 3.14f)GetActor()->SetRotation({ rotation.x, -3.14f, rotation.z, rotation.w });
        if (rotation.z > 3.14f)GetActor()->SetRotation({ rotation.x, rotation.y, -3.14f, rotation.w });
    }
    c_sphere.position = GetActor()->GetPosition();
    if (Collision::IntersectSphereVsSphere(c_sphere,player->GetSphere()) || run_obj)
    {
        if (player != nullptr)
        {
            DirectX::XMFLOAT3 nvec = GetActor()->GetComponent<Movement>()->GetVelocity();
            DirectX::XMFLOAT3 impulse;
            //吹き飛ばす力
            const float power = /*player->GetComponent<Movement>()->GetMoveSpeed() * 1.2f*/0.1f + Mathf::Length(nvec);
            DirectX::XMFLOAT3 ppos = player->GetPosition();
            float ph = player->GetHeight();
            DirectX::XMVECTOR Object_Position = DirectX::XMLoadFloat3(&GetActor()->GetPosition());
            DirectX::XMVECTOR Player_Position = DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(ppos.x, ppos.y + ph * 0.25f, ppos.z));
            DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Player_Position, Object_Position);
            //Vec = DirectX::XMVector3Normalize(DirectX::XMVectorAdd(Vec, NowVec));
            Vec = DirectX::XMVector3Normalize(Vec);
            DirectX::XMFLOAT3 vec;
            DirectX::XMStoreFloat3(&vec, Vec);


            impulse.x = vec.x * power;
            impulse.y = vec.y * power;
            impulse.z = vec.z * power;
            GetActor()->GetComponent<Movement>()->SetVelocity({ 0,0,0 });
            GetActor()->GetComponent<Movement>()->AddImpulse(impulse);
        }
        run_obj = true;
    }
    else
    {
        DirectX::XMFLOAT3 impulse = { 0,0.01f,0 };
        if (GetActor()->GetPosition().y > default_position.y + 4)
        {

            impulse.y = -0.01f;
        }
        GetActor()->GetComponent<Movement>()->AddImpulse(impulse);
    }
}

void ApproachingCollisionObject::DrawImGui()
{
    ImGui::SliderFloat("Radius", &c_sphere.radius, 0.1f, 10.0f);
    if (ImGui::Button("Run"))
    {
        run_obj = true;
    }
}

void ApproachingCollisionObject::DrawDebug()
{
    // デバッグ球描画
    {
        DirectX::XMFLOAT3 position = GetActor()->GetPosition();
        float radius = GetActor()->GetRadius();
        float height = GetActor()->GetHeight();
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
        Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 1, 0, 1);
        Graphics::Instance().GetDebugRenderer()->DrawSphere(c_sphere.position, c_sphere.radius, color);
    }
}
