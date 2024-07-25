#include "Enemy.h"
#include "Mathf.h"
#include "ApproachingTimeObject.h"

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
    Move(elapsedTime);
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
        if(!test_flg)
        {
            const char* filename = "Data/Model/Cube/Cube.mdl";
            std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
            std::string name =std::string("DeadAfterObject:") + std::string(GetActor()->GetName());
            actor->LoadModel(filename);
            actor->SetName(name);
            DirectX::XMFLOAT3 position = GetActor()->GetPosition();
            actor->SetPosition({ position.x, position.y+3, position.z });
            actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
            actor->SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
            actor->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
            actor->SetRadius(3.0f);
            actor->SetActorType(ActorType::Object);
            actor->AddComponent<VsCollision>();
            actor->AddComponent<Movement>();
            actor->AddComponent<ApproachingTimeObject>();
            actor->GetComponent<ApproachingTimeObject>()->SetMaxRuntimer(1.0*60.0f);
            test_flg = true;
        }
    }
    GetActor()->SetRayPosition(GetActor()->GetPosition());
    Character::Update(elapsedTime);
}

void Enemy::DrawImGui()
{
    Character::DrawImGui();
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

void Enemy::Move(float elapsedTime)
{
    //Player* player = ActorManager::Instance().GetActor<Player>("Player");
    //DirectX::XMFLOAT3 target = player->GetActor()->GetPosition();
    Actor* player = ActorManager::Instance().GetActor("Player");
    DirectX::XMFLOAT3 target = player->GetPosition();
    //DirectX::XMFLOAT3 distance=Mathf::Distance3(GetActor().get()->GetPosition(), target);
    //movement.get()->Turn(distance, elapsedTime);
    //movement.get()->Move(distance, elapsedTime);
    DirectX::XMFLOAT3 position=GetActor()->GetPosition();
}
