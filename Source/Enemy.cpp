#include "Enemy.h"
#include "Mathf.h"
#include "TrackingObject.h"

void Enemy::Start()
{
    GetActor()->SetHealth(GetActor()->GetMaxHealth());
    movement = GetActor()->GetComponent<Movement>();
    movement.get()->SetMoveSpeed(1.0f);
    vs_collision=GetActor()->GetComponent<VsCollision>();
    GetActor()->SetAttitudeControlFlag(true);
    //GetActor().get()->SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    // 適当にモーション再生
    Model* model = GetActor()->GetModel();
    if (model != nullptr)
    {
        //model->PlayAnimation(20, true);
    }
}

void Enemy::Update(float elapsedTime)
{
    //エネミー同士の衝突判定
    if (vs_collision->CylinderVsCylinderPushing(ActorType::Enemy,nullptr))
    {

    }
    ////RayCast
    //{
    //    vs_collision->RayCastAxisXZ(ActorType::Stage);
    //    vs_collision->RayCastAxisY(ActorType::Stage);
    //}
    if (GetActor()->GetHealth() <= 0)
    {
        GetActor()->SetDeadFlag(true);
        {
            for (int i = 0; i < 20; i++)
            {
                const char* filename = "Data/Model/Cube/Cube.mdl";
                std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
                std::string name = std::string("ApproachingTimeObject:") + std::string(GetActor()->GetName()) + std::string(":") + std::to_string(i);
                actor->LoadModel(filename);
                actor->SetName(name);
                DirectX::XMFLOAT3 position = GetActor()->GetPosition();
                actor->SetPosition({ position.x, position.y + 3, position.z });
                actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
                actor->SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
                actor->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 0.5f));
                actor->SetRadius(3.0f);
                actor->SetActorType(ActorType::Object);
                actor->AddComponent<VsCollision>();
                actor->AddComponent<Movement>();
                actor->AddComponent<TrackingObject>();
                actor->GetComponent<TrackingObject>()->SetMaxRuntimer((rand() % 4 + static_cast<float>(rand() % 1000)/1000) * 60.0f);
                actor->GetComponent<TrackingObject>()->SetHitCollisionType(HitCollisionType::Damage);
                actor->GetComponent<TrackingObject>()->SetSphereRadius(0.0f);
                actor->GetComponent<TrackingObject>()->SetHitNum(1.0f);
                actor->GetComponent<TrackingObject>()->SetTargetActorType(ActorType::Player);
                actor->GetComponent<TrackingObject>()->SetDesiredPosition({ position.x + (rand() % 30 - 10), position.y + 3+ (rand() % 20), position.z + (rand() % 30 - 10) });
            }
            ActorManager::Instance().Remove(GetActor());
        }
    }
    GetActor()->SetRayPosition(GetActor()->GetPosition());
    Character::Update(elapsedTime);
}

void Enemy::DrawImGui()
{
    Character::DrawImGui();
    if (ImGui::Button("Delete"))
    {
        GetActor()->SetHealth(0);
    }
}

void Enemy::DrawDebug()
{
    // デバッグ球描画
    DirectX::XMFLOAT3 position = GetActor()->GetPosition();
    float radius = GetActor()->GetRadius();
    float height = GetActor()->GetHeight();
    DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
    Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
    //衝突判定用のデバッグ円柱を描画
    Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, radius, height, color);
}
