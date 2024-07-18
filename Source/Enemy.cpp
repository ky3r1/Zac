#include "Enemy.h"
#include "Mathf.h"

void Enemy::Start()
{
    movement = GetActor()->GetComponent<Movement>();
    movement.get()->SetMoveSpeed(1.0f);
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
}

void Enemy::DrawImGui()
{
}

void Enemy::DrawDebug()
{
    // デバッグ球描画
    DirectX::XMFLOAT3 position = GetActor()->GetPosition();
    DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
    Graphics::Instance().GetDebugRenderer()->DrawSphere(position, 3.0f, color);
}

void Enemy::Move(float elapsedTime)
{
    Actor* player = ActorManager::Instance().GetActor("Player");
    DirectX::XMFLOAT3 target = player->GetPosition();
    //DirectX::XMFLOAT3 distance=Mathf::Distance3(GetActor().get()->GetPosition(), target);
    //movement.get()->Turn(distance, elapsedTime);
    //movement.get()->Move(distance, elapsedTime);
    DirectX::XMFLOAT3 position=GetActor()->GetPosition();
}
