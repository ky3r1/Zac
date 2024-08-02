#include "TrackingObject.h"
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
    movement->SetGravity(0.0f);
    movement->SetFriction({ 0.0f});
    movement->SetMoveSpeed(1.0f);
}

void TrackingObject::Update(float elapsedTime)
{
    CollisionObject::Update(elapsedTime);
    //Ž€–S
    {
        if (target_actor != nullptr)
        {
            float r_h = target_actor->GetRadius()*0.9f;
            Sphere p_scphere = { ppos, r_h };
            r_h = GetActor()->GetRadius() * 0.9f;
            Sphere c2_sphere = { c_sphere.position, r_h };
            //{
            //    DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.1, 0.8, 0.25, 1);
            //    Graphics::Instance().GetDebugRenderer()->DrawSphere(p_scphere.position, p_scphere.radius, color);
            //    color = DirectX::XMFLOAT4(0.77, 0.2, 0.5, 1);
            //    Graphics::Instance().GetDebugRenderer()->DrawSphere(c2_sphere.position, c2_sphere.radius, color);
            //}
            if (timer > delete_timer
                //Œë·‚ÍGetActor()->GetRadius()‚Ì‚æ‚è¬‚³‚­‚µ‚È‚¢‚Æ“–‚½‚è”»’è‚ª‚Å‚«‚È‚¢
                || Collision::IntersectSphereVsSphere(c2_sphere, p_scphere)
                )
            {
                GetActor()->SetDeadFlag(true);
                ActorManager::Instance().Remove(GetActor());
            }
        }
    }
    //‰ñ“]
    {
        DirectX::XMFLOAT4 rotation = GetActor()->GetRotation();
        float rot = 0.1f / 3.14f;
        GetActor()->SetRotation({ rotation.x + rot, rotation.y, rotation.z + rot, rotation.w });
        if (rotation.x > 3.14f)GetActor()->SetRotation({ -3.14f, rotation.y, rotation.z, rotation.w });
        if (rotation.y > 3.14f)GetActor()->SetRotation({ rotation.x, -3.14f, rotation.z, rotation.w });
        if (rotation.z > 3.14f)GetActor()->SetRotation({ rotation.x, rotation.y, -3.14f, rotation.w });
    }
    c_sphere.position = GetActor()->GetPosition();
    if (target_actor != nullptr)
    {

        if (timer > max_runtimer || run_obj)
        {
            //‰~Œ`”ÍˆÍ“à‚É‚¢‚é‚Æ‚«‚¾‚¯ƒ^[ƒQƒbƒg‚ÌˆÊ’uî•ñ‚ðXV‚·‚é(c_sphere.radius‚ÅŒø‰Ê”ÍˆÍ‚ð•ÏX:0‚Å”ñŠ®‘S’Ç], FLT_MAX‚ÅŠ®‘S’Ç])
            if (Collision::IntersectSphereVsSphere(c_sphere, target_actor->GetSphere()))
            {
                ppos = target_actor->GetPosition();
            }

            DirectX::XMFLOAT3 nvec = GetActor()->GetComponent<Movement>()->GetVelocity();
            DirectX::XMFLOAT3 impulse;
            //‘¬—Í
            const float power = /*player->GetComponent<Movement>()->GetMoveSpeed() * 1.2f*/0.1f + Mathf::Length(nvec);
            //DirectX::XMFLOAT3 ppos = target_actor->GetPosition();
            float ph = target_actor->GetHeight();
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

            run_obj = true;
        }
        else
        {
            ppos = target_actor->GetPosition();
            if (!desired_flg)
            {
                {
                    DirectX::XMFLOAT3 nvec = GetActor()->GetComponent<Movement>()->GetVelocity();
                    DirectX::XMFLOAT3 impulse;
                    //‚«”ò‚Î‚·—Í
                    const float power = /*player->GetComponent<Movement>()->GetMoveSpeed() * 1.2f*/0.1f + Mathf::Length(nvec);
                    DirectX::XMVECTOR Object_Position = DirectX::XMLoadFloat3(&GetActor()->GetPosition());
                    DirectX::XMVECTOR Desired_Position = DirectX::XMLoadFloat3(&desired_position);
                    DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Desired_Position, Object_Position);
                    Vec = DirectX::XMVector3Normalize(Vec);
                    DirectX::XMFLOAT3 vec;
                    DirectX::XMStoreFloat3(&vec, Vec);

                    impulse.x = vec.x * power;
                    impulse.y = vec.y * power;
                    impulse.z = vec.z * power;
                    GetActor()->GetComponent<Movement>()->SetVelocity({ 0,0,0 });
                    GetActor()->GetComponent<Movement>()->AddImpulse(impulse);
                }
                Sphere s = { desired_position ,1.0f };
                if (Collision::IntersectSphereVsSphere(s, GetActor()->GetSphere()))
                {
                    GetActor()->GetComponent<Movement>()->SetVelocity({ 0,0,0 });
                    desired_flg = true;
                }
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
    }
    timer++;
}

void TrackingObject::DrawImGui()
{
    CollisionObject::DrawImGui();
    ImGui::SliderFloat("Radius", &c_sphere.radius, 0.1f, 10.0f);
    if (ImGui::Button("Run"))
    {
        run_obj = true;
    }
}

void TrackingObject::DrawDebug()
{
    // ƒfƒoƒbƒO‹…•`‰æ
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
