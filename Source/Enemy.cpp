#include "Enemy.h"
#include "Mathf.h"

void Enemy::Start()
{
    movement = GetActor()->GetComponent<Movement>();
    movement.get()->SetMoveSpeed(1.0f);
    vs_collision=GetActor()->GetComponent<VsCollision>();
    //GetActor().get()->SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    // �K���Ƀ��[�V�����Đ�
    Model* model = GetActor()->GetModel();
    if (model != nullptr)
    {
        //model->PlayAnimation(20, true);
    }
}

void Enemy::Update(float elapsedTime)
{
    Move(elapsedTime);
    Actor* dummy = nullptr;
    //�G�l�~�[���m�̏Փ˔���
    if (vs_collision->CylinderVsCylinderPushing(ActorType::Enemy,&dummy))
    {

    }
    ////RayCast
    //{
    //    vs_collision->RayCastAxisXZ(ActorType::Stage);
    //    vs_collision->RayCastAxisY(ActorType::Stage);
    //}
    Character::Update(elapsedTime);
}

void Enemy::DrawImGui()
{
    Character::DrawImGui();
}

void Enemy::DrawDebug()
{
    // �f�o�b�O���`��
    DirectX::XMFLOAT3 position = GetActor()->GetPosition();
    float radius = GetActor()->GetRadius();
    float height = GetActor()->GetHeight();
    DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
    Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
    //�Փ˔���p�̃f�o�b�O�~����`��
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
