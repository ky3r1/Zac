#include "Enemy.h"

#include "Movement.h"
#include "VsCollision.h"
#include "Gravity.h"

#include "CollisionObject.h"
#include "TrackingObject.h"
#include "TimeTrackingObject.h"

#include "Mathf.h"
#include "StageManager.h"

#include "AI/BehaviorTree.h"
#include "AI/BehaviorData.h"
#include "AI/NodeBase.h"
#include "AI/JudgmentDerived.h"
#include "AI/ActionDerived.h"

#define ATTACKTIMER 2.0f*60;

void Enemy::Start()
{
    GetActor()->AddComponent<Character>();
    GetActor()->GetComponent<Character>()->SetHealth(GetActor()->GetComponent<Character>()->GetMaxHealth());  
    GetActor()->AddComponent<Movement>();
    GetActor()->GetComponent<Movement>()->SetMoveSpeed(50.0f);
    GetActor()->AddComponent<Gravity>();
    GetActor()->AddComponent<VsCollision>();

    //float points = 50;
    //waypoints =
    //{
    //                                //        0        1         2
    //    {{-points,0,points},0},     //    // �E�[�[�[�[ �E�[�[�[�[�E
    //    {{0,0,points},1},           //    // �b        �b        �b
    //    {{points,0,points},2},      //    // �b        �b        �b
    //    {{points,0,0},3},           //    // �b       8�b        �b
    //    {{points,0,-points},4},     //    //7�E�[�[�[�[ �E�[�[�[�[�E3
    //    {{0,0,-points},5},          //    // �b        �b        �b
    //    {{-points,0,-points},6},    //    // �b        �b        �b
    //    {{-points,0,0},7},          //    // �b        �b        �b
    //    {{0,0,0},8},                //    // �E�[�[�[�[ �E�[�[�[�[�E
    //                                //        6        5         4
    //};
    //dijkstra_algorithm = new DijkstraAlgorithm(waypoints.size());
    //auto add_edge = [&](int from, int to)
    //{
    //    edge.push_back({ waypoints[from].position, waypoints[to].position });
    //    dijkstra_algorithm->edge(from, to, Mathf::Distance(waypoints[from].position, waypoints[to].position));
    //};
    //add_edge(0, 1);
    //add_edge(0, 7);
    //add_edge(1, 2);
    //add_edge(1, 8);
    //add_edge(2, 3);
    //add_edge(3, 4);
    //add_edge(3, 8);
    //add_edge(4, 5);
    //add_edge(5, 6);
    //add_edge(5, 8);
    //add_edge(6, 7);
    //add_edge(7, 8);

    //Ai
    {
        //// �r�w�C�r�A�c���[�ݒ�
        //behaviorData = new BehaviorData();
        //aiTree = new BehaviorTree();
        //// BehaviorTree�}�����BehaviorTree���\�z
        //// �m�[�h��ǉ�
        //aiTree->AddNode("", "Root", 0, BehaviorTree::SelectRule::Priority, nullptr, nullptr);
        //aiTree->AddNode("Root", "Escape", 3, BehaviorTree::SelectRule::Sequence, new EscapeJudgment(this), nullptr);
        //aiTree->AddNode("Root", "Battle", 4, BehaviorTree::SelectRule::Priority, new BattleJudgment(this), nullptr);
        //aiTree->AddNode("Root", "Scout", 5, BehaviorTree::SelectRule::Priority, nullptr, nullptr);


        //aiTree->AddNode("Scout", "Wander", 1, BehaviorTree::SelectRule::Non, new WanderJudgment(this), new WanderAction(this));
        //aiTree->AddNode("Scout", "Idle", 2, BehaviorTree::SelectRule::Non, nullptr, new IdleAction(this));


        //aiTree->AddNode("Battle", "Attack", 1, BehaviorTree::SelectRule::Priority, new AttackJudgment(this), nullptr);
        //aiTree->AddNode("Attack", "ShortAttack", 1, BehaviorTree::SelectRule::Non, new ShortAttackJudgment(this), new NormalAction(this)/*nullptr*/);
        ////aiTree->AddNode("ShortAttack", "Normal", 1, BehaviorTree::SelectRule::Non, nullptr, new NormalAction(this));
        //
        //aiTree->AddNode("Attack", "LongAttack", 2, BehaviorTree::SelectRule::Non, new LongAttackJudgment(this), new SkillAction(this)/*nullptr*/);
        ////aiTree->AddNode("LongAttack", "Skill", 1, BehaviorTree::SelectRule::Non, nullptr, new SkillAction(this));

        //aiTree->AddNode("Battle", "Pursuit", 2, BehaviorTree::SelectRule::Non, nullptr, new PursuitAction(this));

        //aiTree->AddNode("Escape", "Leave", 1, BehaviorTree::SelectRule::Non, new EscapeJudgment(this), new LeaveAction(this));
        //aiTree->AddNode("Escape", "Recover", 2, BehaviorTree::SelectRule::Non, nullptr, new RecoverAction(this));
    }

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
    
    GetActor()->UpdateDelayTime(attack_flag, 2.0f*60.0f);
    //Djikstra
    {     
        //���[�h
        DirectX::XMFLOAT3 position = GetActor()->GetPosition();
        DirectX::XMFLOAT3 target_position = ActorManager::Instance().GetPlayer()->GetPosition();
        DijkstraAlgorithm* dijkstra_algorithm = StageManager::Instance().GetDijkstraAlgorithm();
        std::vector<WayPoint> vector_way_p = dijkstra_algorithm->GetWayPoints();
      
        //Target��WayPoint��ID���ς���Ă��� or Enemy���I�_�܂ōs�����Ƃ�
        int t_id = dijkstra_algorithm->GetNearWayPointId(target_position);
        if (t_id != target_id)
        {
            target_id = t_id;
            //�K�ꂽ�|�C���g�����Z�b�g
            dijkstra_algorithm->ReSetVisited(visited);

            //�ŒZ�o�H�T��
            shortest_path = dijkstra_algorithm->GetPath(position, target_id);
            //�ŏI�|�C���g�̍��W��ۑ�
            last_waypoint = vector_way_p.at(shortest_path.at(shortest_path.size() - 1)).position;
        }
        else
        { 
            float d = 0;
            //�ŒZ�o�H��͈̓x�[�Xfor���Ŏ���
            for(int i: shortest_path)
            {   

                WayPoint way_p = dijkstra_algorithm->GetWayPoints().at(i);
                if (visited.at(shortest_path.at(shortest_path.size() - 1)))break;
                //�K��Ă����Ȃ�v�Z�̕K�v���Ȃ��̂�continue
                if (visited.at(i)) continue;
                //�ڕW�܂ňړ�
                next_waypoint =way_p.position;
                GetActor()->GetComponent<Movement>()->MoveTarget(next_waypoint, elapsedTime);
                //�ڕW�܂œ��B���Ă����玟�̖ڕW�n�_�ɐi��
                //���B���Ă��Ȃ��Ȃ玟�̖ړI�n����肽���Ȃ��̂�break��for���𔲂���
                d = Mathf::Distance(position, way_p.position);
                if (d < way_p.radius)
                {
                    visited.at(i) = true;
                }
                else break;
            }
        }
    }
    //�G�l�~�[���m�̏Փ˔���
    if (GetActor()->GetComponent<VsCollision>()->CylinderVsCylinderPushing(ActorType::Enemy, nullptr))
    {

    }
    if (GetActor()->GetComponent<Character>()->GetHealth() <= 0)
    {
        {
            for (int i = 0; i < 20; i++)
            {
                const char* filename = "Data/Model/Cube/Cube.mdl";
                std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
                std::string name = std::string("TrackingObject:") + std::string(GetActor()->GetName()) + std::string(":") + std::to_string(i);
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
                actor->AddComponent<CollisionObject>();
                actor->GetComponent<CollisionObject>()->SetTargetActorType(ActorType::Player);
                actor->GetComponent<CollisionObject>()->SetHitCollisionType(HitCollisionType::Damage);
                actor->GetComponent<CollisionObject>()->SetHitNum(1.0f);

                actor->AddComponent<TrackingObject>();
                actor->GetComponent<TrackingObject>()->SetSphereRadius(0.0f);
                actor->GetComponent<TrackingObject>()->SetDesiredPosition({ position.x + (rand() % 30 - 10), position.y + 3+ (rand() % 20), position.z + (rand() % 30 - 10) });
            
                actor->AddComponent<TimeTrackingObject>();
                actor->GetComponent<TimeTrackingObject>()->SetRunTimer((rand() % 4 + static_cast<float>(rand() % 1000) / 1000) * 60.0f);
            }
            ActorManager::Instance().Remove(GetActor());
        }
    }
}

void Enemy::ShotObject()
{
    const char* filename = "Data/Model/Cube/Cube.mdl";
    std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
    std::string name = std::string("TrackingObject:") + std::string(GetActor()->GetName()) + std::string(":") + std::string("Shot");
    actor->LoadModel(filename);
    actor->SetName(name);
    DirectX::XMFLOAT3 position = GetActor()->GetPosition();
    actor->SetPosition({ position.x, position.y + 3, position.z });
    actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
    actor->SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    actor->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.5f));
    actor->SetRadius(3.0f);
    actor->SetActorType(ActorType::Object);
    actor->AddComponent<VsCollision>();
    actor->AddComponent<Movement>();
    actor->AddComponent<CollisionObject>();
    actor->GetComponent<CollisionObject>()->SetTargetActorType(ActorType::Player);
    actor->GetComponent<CollisionObject>()->SetHitCollisionType(HitCollisionType::Damage);
    actor->GetComponent<CollisionObject>()->SetHitNum(1.0f);
    actor->AddComponent<TrackingObject>();
    actor->GetComponent<TrackingObject>()->Run();
    //actor->GetComponent<TrackingObject>()->SetHitCollisionType(HitCollisionType::Damage);
    //actor->GetComponent<TrackingObject>()->SetHitNum(1.0f);
    //actor->GetComponent<TrackingObject>()->SetTargetActorType(ActorType::Player);
    ////actor->GetComponent<TrackingObject>()->SetDesiredPosition({ position.x + (rand() % 30 - 10), position.y + 3 + (rand() % 20), position.z + (rand() % 30 - 10) });
}

bool Enemy::Search(DirectX::XMFLOAT3 target_position_s)
{
    if (Collision::SphereInPoint(GetActor()->GetPosition(), search_range, target_position_s))return true;
    return false;
}

void Enemy::DrawImGui()
{
    if (ImGui::Button("Delete"))
    {
        GetActor()->GetComponent<Character>()->SetHealth(0);
    }
}

void Enemy::DrawDebug()
{
    // �f�o�b�O���`��
    DirectX::XMFLOAT3 position = GetActor()->GetPosition();
    float radius = GetActor()->GetRadius();
    float height = GetActor()->GetHeight();
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
        //�����蔻��p�̃f�o�b�O����`��
        Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
        //�Փ˔���p�̃f�o�b�O�~����`��
        Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, radius, height, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 1, 1);
        //�ߐڍU���͈�
        Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, short_attack_range, 1.0f, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.8f, 0.3f, 0.3f, 1);
        //�������U���͈�
        Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, long_attack_range, 1.0f, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 1, 0, 1);
        //���G�͈�
        Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, search_range, 1.0f, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.0f, 0.5f, 1.0f, 1);
        //�����蔻��p�̃f�o�b�O����`��
        Graphics::Instance().GetDebugRenderer()->DrawSphere(target_position, 3.0f, color);
    }

    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 0.3f, 0.8f, 1);
        //�����蔻��p�̃f�o�b�O����`��
        Graphics::Instance().GetDebugRenderer()->DrawSphere(next_waypoint, 2.0f, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.4f, 1);
        //�����蔻��p�̃f�o�b�O����`��
        Graphics::Instance().GetDebugRenderer()->DrawSphere(last_waypoint, 2.0f, color);
    }
}
