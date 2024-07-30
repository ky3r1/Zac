#include "Enemy.h"
#include "Mathf.h"
#include "TrackingObject.h"

//#include "BehaviorTree.h"
//#include "BehaviorData.h"
//#include "NodeBase.h"
//#include "ActionBehavior.h"
//#include "JudgmentBehavior.h"

void Enemy::Start()
{
    GetActor()->SetHealth(GetActor()->GetMaxHealth());
    movement = GetActor()->GetComponent<Movement>();
    movement.get()->SetMoveSpeed(1.0f);
    vs_collision=GetActor()->GetComponent<VsCollision>();
    GetActor()->SetAttitudeControlFlag(true);
    //GetActor().get()->SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    //// ビヘイビアツリー設定
    //behaviorData = new BehaviorData();
    //aiTree = new BehaviorTree();
    //// BehaviorTree図を基にBehaviorTreeを構築
    //// ノードを追加
    //GetActor()->AddComponent<EscapeJudgment>();
    //aiTree->AddNode("", "Root", 0, BehaviorTree::SelectRule::Priority, nullptr, nullptr);
    //aiTree->AddNode("Root", "Escape", 3, BehaviorTree::SelectRule::Sequence, new EscapeJudgment(), nullptr);
    //aiTree->AddNode("Root", "Battle", 4, BehaviorTree::SelectRule::Priority, new BattleJudgment(), nullptr);
    //aiTree->AddNode("Root", "Scout", 5, BehaviorTree::SelectRule::Priority, nullptr, nullptr);


    //aiTree->AddNode("Scout", "Wander", 1, BehaviorTree::SelectRule::Non, new WanderJudgment(), new WanderAction());
    //aiTree->AddNode("Scout", "Idle", 2, BehaviorTree::SelectRule::Non, nullptr, new IdleAction());

    //aiTree->AddNode("Battle", "Attack", 1, BehaviorTree::SelectRule::Random, new AttackJudgment(), nullptr);
    //aiTree->AddNode("Attack", "Normal", 1, BehaviorTree::SelectRule::Non, nullptr, new NormalAction());
    //aiTree->AddNode("Attack", "Skill", 2, BehaviorTree::SelectRule::Non, nullptr, new SkillAction());

    //aiTree->AddNode("Battle", "Pursuit", 2, BehaviorTree::SelectRule::Non, nullptr, new PursuitAction());

    //aiTree->AddNode("Escape", "Leave", 1, BehaviorTree::SelectRule::Non, new EscapeJudgment(), new LeaveAction());
    //aiTree->AddNode("Escape", "Recover", 2, BehaviorTree::SelectRule::Non, nullptr, new RecoverAction());

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
    // デバッグ球描画
    DirectX::XMFLOAT3 position = GetActor()->GetPosition();
    float radius = GetActor()->GetRadius();
    float height = GetActor()->GetHeight();
    DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
    Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
    //衝突判定用のデバッグ円柱を描画
    Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, radius, height, color);
}
