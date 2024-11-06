#include "Character.h"
#include "VsCollision.h"
#include "Mathf.h"

#define MAX_UNBEATABLE 2.0f*60

Character::Character()
{
}

void Character::Start()
{
}

void Character::Update(float elapsedTime)
{

    GetActor()->GetModel()->SetHitStopAnimationSpeed(GetActor()->GetAnimationSpeed());
    //無敵時間更新
    GetActor()->UpdateDelayTime(unbeatable_delay, MAX_UNBEATABLE);
    //RayCast
    GetActor()->SetRayPosition(GetActor()->GetPosition());
    if(true)
    {
        GetActor()->GetComponent<VsCollision>()->RayCastAxisYUnder();
        GetActor()->GetComponent<VsCollision>()->RayCastAxisXZ();
        //GetActor()->GetComponent<VsCollision>()->RayCastAxisYUp();
        //GetActor()->GetComponent<VsCollision>()->RayCastAxisYUnder();
        //if (GetActor()->GetPosition().y < 0.0f)
        //{
        //    GetActor()->SetPosition({ GetActor()->GetPosition().x, 0.0f, GetActor()->GetPosition().z });
        //}
    }
    else
    {
        if (GetActor()->GetPosition().y < 0.0f)
        {
            GetActor()->SetPosition({ GetActor()->GetPosition().x, 0.0f, GetActor()->GetPosition().z });
        }
    }
}

void Character::DrawImGui()
{
    ImGui::SliderFloat("health", &current_health, 0.0f, max_health);
}

void Character::DrawDebug()
{
    // デバッグ球描画
    DirectX::XMFLOAT3 position = GetActor()->GetPosition();
    float radius = GetActor()->GetRadius();
    float height = GetActor()->GetHeight();
    DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
    Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
    //衝突判定用のデバッグ円柱を描画
    Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, radius, height, color);
    {
        float linescale = 10.0f;
        color = DirectX::XMFLOAT4(0, 0, 1, 1);
        //正面の方向取得
        Graphics::Instance().GetLineRenderer()->Line(
            { position.x,position.y + height * 0.5f,position.z },
            Mathf::Add({ position.x,position.y + height * 0.5f,position.z }, { GetActor()->GetFront().x / GetActor()->GetScale().x * linescale,GetActor()->GetFront().y / GetActor()->GetScale().y * linescale,GetActor()->GetFront().z / GetActor()->GetScale().z * linescale }),
            color);
    }
}

void Character::TakeDamage(float damage)
{
    current_health -= damage;
}

void Character::TakeHeel(float heel)
{
    current_health += heel;
}
