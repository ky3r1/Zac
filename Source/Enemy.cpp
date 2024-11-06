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
    //    {{-points,0,points},0},     //    // ・ーーーー ・ーーーー・
    //    {{0,0,points},1},           //    // ｜        ｜        ｜
    //    {{points,0,points},2},      //    // ｜        ｜        ｜
    //    {{points,0,0},3},           //    // ｜       8｜        ｜
    //    {{points,0,-points},4},     //    //7・ーーーー ・ーーーー・3
    //    {{0,0,-points},5},          //    // ｜        ｜        ｜
    //    {{-points,0,-points},6},    //    // ｜        ｜        ｜
    //    {{-points,0,0},7},          //    // ｜        ｜        ｜
    //    {{0,0,0},8},                //    // ・ーーーー ・ーーーー・
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
        //// ビヘイビアツリー設定
        //behaviorData = new BehaviorData();
        //aiTree = new BehaviorTree();
        //// BehaviorTree図を基にBehaviorTreeを構築
        //// ノードを追加
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

    // 適当にモーション再生
    Model* model = GetActor()->GetModel();
    if (model != nullptr)
    {
        //model->PlayAnimation(20, true);
    }
}

void Enemy::Update(float elapsedTime)
{
    //// 現在実行されているノードが無ければ
    //if (activeNode == nullptr)
    //{
    //    // 次に実行するノードを推論する。
    //    activeNode = aiTree->ActiveNodeInference(behaviorData);
    //}
    //// 現在実行するノードがあれば
    //if (activeNode != nullptr)
    //{
    //    // ビヘイビアツリーからノードを実行。
    //    activeNode = aiTree->Run(activeNode, behaviorData, elapsedTime);
    //}
    
    GetActor()->UpdateDelayTime(attack_flag, 2.0f*60.0f);
    //Djikstra
    {     
        //ロード
        DirectX::XMFLOAT3 position = GetActor()->GetPosition();
        DirectX::XMFLOAT3 target_position = ActorManager::Instance().GetPlayer()->GetPosition();
        DijkstraAlgorithm* dijkstra_algorithm = StageManager::Instance().GetDijkstraAlgorithm();
        std::vector<WayPoint> vector_way_p = dijkstra_algorithm->GetWayPoints();
      
        //TargetのWayPointのIDが変わっている or Enemyが終点まで行ったとき
        int t_id = dijkstra_algorithm->GetNearWayPointId(target_position);
        if (t_id != target_id)
        {
            target_id = t_id;
            //訪れたポイントをリセット
            dijkstra_algorithm->ReSetVisited(visited);

            //最短経路探索
            shortest_path = dijkstra_algorithm->GetPath(position, target_id);
            //最終ポイントの座標を保存
            last_waypoint = vector_way_p.at(shortest_path.at(shortest_path.size() - 1)).position;
        }
        else
        { 
            float d = 0;
            //最短経路を範囲ベースfor文で周す
            for(int i: shortest_path)
            {   

                WayPoint way_p = dijkstra_algorithm->GetWayPoints().at(i);
                if (visited.at(shortest_path.at(shortest_path.size() - 1)))break;
                //訪れていたなら計算の必要がないのでcontinue
                if (visited.at(i)) continue;
                //目標まで移動
                next_waypoint =way_p.position;
                GetActor()->GetComponent<Movement>()->MoveTarget(next_waypoint, elapsedTime);
                //目標まで到達していたら次の目標地点に進む
                //到達していないなら次の目的地を取りたくないのでbreakでfor文を抜ける
                d = Mathf::Distance(position, way_p.position);
                if (d < way_p.radius)
                {
                    visited.at(i) = true;
                }
                else break;
            }
        }
    }
    //エネミー同士の衝突判定
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
    // デバッグ球描画
    DirectX::XMFLOAT3 position = GetActor()->GetPosition();
    float radius = GetActor()->GetRadius();
    float height = GetActor()->GetHeight();
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
        //当たり判定用のデバッグ球を描画
        Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
        //衝突判定用のデバッグ円柱を描画
        Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, radius, height, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 1, 1);
        //近接攻撃範囲
        Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, short_attack_range, 1.0f, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.8f, 0.3f, 0.3f, 1);
        //遠距離攻撃範囲
        Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, long_attack_range, 1.0f, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 1, 0, 1);
        //索敵範囲
        Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, search_range, 1.0f, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.0f, 0.5f, 1.0f, 1);
        //当たり判定用のデバッグ球を描画
        Graphics::Instance().GetDebugRenderer()->DrawSphere(target_position, 3.0f, color);
    }

    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 0.3f, 0.8f, 1);
        //当たり判定用のデバッグ球を描画
        Graphics::Instance().GetDebugRenderer()->DrawSphere(next_waypoint, 2.0f, color);
    }
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.4f, 1);
        //当たり判定用のデバッグ球を描画
        Graphics::Instance().GetDebugRenderer()->DrawSphere(last_waypoint, 2.0f, color);
    }
}
