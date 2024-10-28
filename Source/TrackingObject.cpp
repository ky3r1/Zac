#include "TrackingObject.h"

#include "CollisionObject.h"

#include "Movement.h"
#include "VsCollision.h"

#include "Mathf.h"

TrackingObject::TrackingObject()
{
}

TrackingObject::~TrackingObject()
{
}

void TrackingObject::Start()
{
    if (Mathf::Equal(desired_position, DirectX::XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX)))
    {
        desired_position = GetActor()->GetPosition();
    }
    default_position = desired_position;
    Movement* movement = GetActor()->GetComponent<Movement>().get();
    movement->SetFriction({ 0.000f});
    movement->SetMoveSpeed(100.0f);
}

void TrackingObject::Update(float elapsedTime)
{
    Actor* target_actor = GetActor()->GetComponent<CollisionObject>()->GetTargetActor();
    //回転
    {
        DirectX::XMFLOAT4 rotation = GetActor()->GetRotation();
        float rot = 0.1f / 3.14f;
        GetActor()->SetRotation({ rotation.x + rot, rotation.y, rotation.z + rot, rotation.w });
        if (rotation.x > 3.14f)GetActor()->SetRotation({ -3.14f, rotation.y, rotation.z, rotation.w });
        if (rotation.y > 3.14f)GetActor()->SetRotation({ rotation.x, -3.14f, rotation.z, rotation.w });
        if (rotation.z > 3.14f)GetActor()->SetRotation({ rotation.x, rotation.y, -3.14f, rotation.w });
    }

    
    
    if (target_actor != nullptr)
    { 
        c_sphere.position = GetActor()->GetPosition();
        //当たらなかったときの削除(目標近くで削除)  
        {
            float r_h = target_actor->GetRadius() * 0.9f;
            Sphere t_scphere = { tpos, r_h };
            r_h = GetActor()->GetRadius() * 0.9f;
            Sphere c2_sphere = { c_sphere.position, r_h };
            if (timer > delete_timer
                //誤差はGetActor()->GetRadius()のより小さくしないと当たり判定ができない
                || Collision::IntersectSphereVsSphere(c2_sphere, t_scphere)
                )
            {
                ActorManager::Instance().Remove(GetActor());
            }
        }

        //目標の追跡
        if (run_obj)
        {
            //円形範囲内にいるときだけターゲットの位置情報を更新する(c_sphere.radiusで効果範囲を変更:0で非完全追従, FLT_MAXで完全追従)
            if (Collision::IntersectSphereVsSphere(c_sphere, target_actor->GetSphere()))
            {
                tpos = target_actor->GetPosition();
            }
            DirectX::XMFLOAT3 impulse;
            //速力
            float power = /*player->GetComponent<Movement>()->GetMoveSpeed() * 1.2f*/10.0f+Mathf::Length(GetActor()->GetComponent<Movement>()->GetVelocity());
            //DirectX::XMFLOAT3 ppos = target_actor->GetPosition();
            float th = target_actor->GetHeight();
            DirectX::XMVECTOR Object_Position = DirectX::XMLoadFloat3(&GetActor()->GetPosition());
            DirectX::XMVECTOR Target_Position = DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(tpos.x, tpos.y + th * 0.25f, tpos.z));
            DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Target_Position, Object_Position);
            //Vec = DirectX::XMVector3Normalize(DirectX::XMVectorAdd(Vec, NowVec));
            Vec = DirectX::XMVector3Normalize(Vec);
            DirectX::XMFLOAT3 vec;
            DirectX::XMStoreFloat3(&vec, Vec);

            impulse.x = vec.x * power;
            impulse.y = vec.y * power;
            impulse.z = vec.z * power;
            GetActor()->GetComponent<Movement>()->SetVelocity(impulse);
            run_obj = true;
        }
        else
        {
            tpos = target_actor->GetPosition();
            if (!desired_flg)
            {
                {
                    DirectX::XMFLOAT3 nvec = GetActor()->GetComponent<Movement>()->GetVelocity();
                    DirectX::XMFLOAT3 impulse;
                    float power = /*player->GetComponent<Movement>()->GetMoveSpeed() * 1.2f*/10.f + Mathf::Length(nvec);
                    DirectX::XMVECTOR Object_Position = DirectX::XMLoadFloat3(&GetActor()->GetPosition());
                    DirectX::XMVECTOR Desired_Position = DirectX::XMLoadFloat3(&desired_position);
                    DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Desired_Position, Object_Position);
                    Vec = DirectX::XMVector3Normalize(Vec);
                    DirectX::XMFLOAT3 vec;
                    DirectX::XMStoreFloat3(&vec, Vec);

                    impulse.x = vec.x * power;
                    impulse.y = vec.y * power;
                    impulse.z = vec.z * power;
                    GetActor()->GetComponent<Movement>()->SetVelocity(impulse);
                }
                Sphere s = { desired_position ,1.0f };
                if (Collision::IntersectSphereVsSphere(s, GetActor()->GetSphere()))
                {
                    GetActor()->GetComponent<Movement>()->SetVelocity({ 0,0,0 });
                    desired_flg = true;
                }
            }
        }
    }
    timer++;
}

void TrackingObject::DrawImGui()
{
    ImGui::SliderFloat("Radius", &c_sphere.radius, 0.1f, 10.0f);
    if (ImGui::Button("Run"))
    {
        run_obj = true;
    }
}

void TrackingObject::DrawDebug()
{
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 1, 0, 1);
        Graphics::Instance().GetDebugRenderer()->DrawSphere(c_sphere.position, c_sphere.radius, color);
    }
}
