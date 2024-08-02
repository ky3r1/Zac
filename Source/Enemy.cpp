#include "Enemy.h"
#include "Mathf.h"
#include "TrackingObject.h"

#include "AI/BehaviorTree.h"
#include "AI/BehaviorData.h"
#include "AI/NodeBase.h"
#include "AI/JudgmentDerived.h"
#include "AI/ActionDerived.h"

void Enemy::Start()
{
    GetActor()->SetHealth(GetActor()->GetMaxHealth());
    movement = GetActor()->GetComponent<Movement>();
    movement.get()->SetMoveSpeed(0.08f);
    vs_collision=GetActor()->GetComponent<VsCollision>();
    GetActor()->SetAttitudeControlFlag(true);
    // �r�w�C�r�A�c���[�ݒ�
    behaviorData = new BehaviorData();
    aiTree = new BehaviorTree();
    // BehaviorTree�}�����BehaviorTree���\�z
    // �m�[�h��ǉ�
    aiTree->AddNode("", "Root", 0, BehaviorTree::SelectRule::Priority, nullptr, nullptr);
    aiTree->AddNode("Root", "Escape", 3, BehaviorTree::SelectRule::Sequence, new EscapeJudgment(this), nullptr);
    aiTree->AddNode("Root", "Battle", 4, BehaviorTree::SelectRule::Priority, new BattleJudgment(this), nullptr);
    aiTree->AddNode("Root", "Scout", 5, BehaviorTree::SelectRule::Priority, nullptr, nullptr);


    aiTree->AddNode("Scout", "Wander", 1, BehaviorTree::SelectRule::Non, new WanderJudgment(this), new WanderAction(this));
    aiTree->AddNode("Scout", "Idle", 2, BehaviorTree::SelectRule::Non, nullptr, new IdleAction(this));

    aiTree->AddNode("Battle", "Attack", 1, BehaviorTree::SelectRule::Random, new AttackJudgment(this), nullptr);
    aiTree->AddNode("Attack", "Normal", 1, BehaviorTree::SelectRule::Non, nullptr, new NormalAction(this));
    aiTree->AddNode("Attack", "Skill", 2, BehaviorTree::SelectRule::Non, nullptr, new SkillAction(this));

    aiTree->AddNode("Battle", "Pursuit", 2, BehaviorTree::SelectRule::Non, nullptr, new PursuitAction(this));

    aiTree->AddNode("Escape", "Leave", 1, BehaviorTree::SelectRule::Non, new EscapeJudgment(this), new LeaveAction(this));
    aiTree->AddNode("Escape", "Recover", 2, BehaviorTree::SelectRule::Non, nullptr, new RecoverAction(this));

    // �K���Ƀ��[�V�����Đ�
    Model* model = GetActor()->GetModel();
    if (model != nullptr)
    {
        //model->PlayAnimation(20, true);
    }
}

void Enemy::Update(float elapsedTime)
{
    //// ���ݎ��s����Ă���m�[�h���������
    //if (activeNode == nullptr)
    //{
    //    // ���Ɏ��s����m�[�h�𐄘_����B
    //    activeNode = aiTree->ActiveNodeInference(behaviorData);
    //}
    //// ���ݎ��s����m�[�h�������
    //if (activeNode != nullptr)
    //{
    //    // �r�w�C�r�A�c���[����m�[�h�����s�B
    //    activeNode = aiTree->Run(activeNode, behaviorData, elapsedTime);
    //}

    GetActor()->GetComponent<Movement>()->MoveTarget(ActorManager::Instance().GetPlayer()->GetPosition(), elapsedTime);

    //�G�l�~�[���m�̏Փ˔���
    if (vs_collision->CylinderVsCylinderPushing(ActorType::Enemy,nullptr))
    {

    }
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

bool Enemy::Search(DirectX::XMFLOAT3 target_position_s)
{
    if (Collision::SphereInPoint(GetActor()->GetPosition(), search_range, target_position_s))return true;
    return false;
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
    // �f�o�b�O���`��
    DirectX::XMFLOAT3 position = GetActor()->GetPosition();
    float radius = GetActor()->GetRadius();
    float height = GetActor()->GetHeight();
    DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
    Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
    //�Փ˔���p�̃f�o�b�O�~����`��
    Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, radius, height, color);
}
