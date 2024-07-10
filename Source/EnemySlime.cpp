#include "EnemySlime.h"
#include "Graphics/Graphics.h"
#include "Mathf.h"
#include "Player.h"
#include "Collision.h"

//コンストラクタ
EnemySlime::EnemySlime()
{
    model = new Model("Data/Model/Slime/Slime.mdl");

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 0.01f;

    //幅、高さ設定
    radius = 0.5f;
    height = 1.0f;

    //徘徊ステートへ遷移
    TransitionWanderState();
}

//デストラクタ
EnemySlime::~EnemySlime()
{
    delete model;
}

//更新処理
void EnemySlime::Update(float elapsedTime)
{
    //ステートごとの更新処理
    switch (state)
    {
    case State::Wander:
        UpdateWanderState(elapsedTime);
        break;
    case State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    case State::Pursuit:
        UpdatePursuitState(elapsedTime);
        break;
    case State::Attack:
        UpdateAttackState(elapsedTime);
        break;
    case State::IdleBattle:
        UpdateIdleBattleState(elapsedTime);
        break;
    case State::Damage:
        UpdateDamageState(elapsedTime);
        break;
    case State::Death:
        UpdateDeathState(elapsedTime);
        break;
    }

    //速力処理更新
    UpdateVelocity(elapsedTime);

    //無敵時間更新
    UpdateInvincibleTime(elapsedTime);

    //オブジェクト行列を更新
    UpdateTransform();

    //アニメ更新処理
    model->UpdateAnimation(elapsedTime);
    //モデル行列更新
    model->UpdateTransform(transform);
}

//描画処理
void EnemySlime::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);
}

void EnemySlime::DrewDebugPrimitive()
{
    //基底クラスのデバッグプリミティブ描画
    Enemy::DrewDebugPrimitive();
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

    //縄張り範囲をデバッグ円柱描画
    debugRenderer->DrawCylinder(territoryOrigin, territoryRange, 1.0f, DirectX::XMFLOAT4(0, 1, 0, 1));
    //ターゲット位置をデバッグ球描画
    debugRenderer->DrawSphere(targetPosition, radius, DirectX::XMFLOAT4(1, 1, 0, 1));
    //索敵範囲をデバッグ円柱描画
    debugRenderer->DrawCylinder(position, searchRange, 1.0f, DirectX::XMFLOAT4(0, 0, 1, 1));
}

void EnemySlime::SetTerritory(const DirectX::XMFLOAT3& origin, float range)
{
    territoryOrigin = origin;
    territoryRange = range;
}
bool EnemySlime::SearchPlayer()
{
    // プレイヤーとの高低差を考慮して3Dで距離判定をする
    const DirectX::XMFLOAT3& playerPosition = Player::Instance().GetPosition();
    float vx = playerPosition.x - position.x;
    float vy = playerPosition.y - position.y;
    float vz = playerPosition.z - position.z;
    float dist = sqrtf(vx * vx + vy * vy + vz * vz);

    if (dist < searchRange)
    {
        float distXZ = sqrtf(vx * vx + vz * vz);
        // 単位ベクトル化
        vx /= distXZ;
        vz /= distXZ;

        // 方向ベクトル化
        float frontX = sinf(angle.y);
        float frontZ = cosf(angle.y);
        // 2つのベクトルの内積値で前後判定
        float dot = (frontX * vx) + (frontZ * vz);
        if (dot > 0.0f)
        {
            return true;
        }
    }
    return false;
}

//死亡したときに呼ばれる
void EnemySlime::OnDead()
{
    TransitionDeathState();
}
void EnemySlime::OnDamaged()
{
    //ダメージステートへ移行
    TransitionDamageState();
}

//ターゲット位置をランダム設定
void EnemySlime::SetRandomTargetPosition()
{
    float theta = Mathf::RandomRange(-DirectX::XM_PI, DirectX::XM_PI);
    float range = Mathf::RandomRange(0.0f, territoryRange);
    targetPosition.x = territoryOrigin.x + sinf(theta) * range;
    targetPosition.y = territoryOrigin.y;
    targetPosition.z = territoryOrigin.z + cosf(theta) * range;
}
//目標地点へ移動
void EnemySlime::MoveToTarget(float elapsedTime, float speedRate)
{
    // ターゲット方向への進行ベクトルを算出
    float vx = targetPosition.x - position.x;
    float vz = targetPosition.z - position.z;
    float dist = sqrtf(vx * vx + vz * vz);
    vx /= dist;
    vz /= dist;

    // 移動処理
    Move(vx, vz, moveSpeed * speedRate);
    Turn(elapsedTime, vx, vz, turnSpeed * speedRate);
}

void EnemySlime::CollisionNodeVsPlayer(const char* nodeName, float boneRadius)
{
    //ノード取得
    Model::Node* node = model->FindNode(nodeName);
    if (node != nullptr)
    {
        //ノードの位置取得
        DirectX::XMFLOAT3 nodePosition;
        nodePosition.x = node->worldTransform._41;
        nodePosition.y = node->worldTransform._42;
        nodePosition.z = node->worldTransform._43;

        //当たり判定表示
        Graphics::Instance().GetDebugRenderer()->DrawSphere(nodePosition, boneRadius, DirectX::XMFLOAT4(0, 0, 1, 1));

        Player& player = Player::Instance();
        DirectX::XMFLOAT3 outPosition;
        if (Collision::IntersectSphereVsCylinder(
            nodePosition,
            boneRadius,
            player.GetPosition(),
            player.GetRadius(),
            player.GetHealth(),
            outPosition
        ))
        {
            //ダメージを与える
            if (player.ApplyDamage(1, 0.5f))
            {
                //敵を吹き飛ばすベクトルを算出
                DirectX::XMFLOAT3 vec;
                vec.x = outPosition.x - nodePosition.x;
                vec.z = outPosition.z - nodePosition.z;
                float length = sqrtf(vec.x * vec.x + vec.z * vec.z);
                vec.x /= length;
                vec.z /= length;

                //XZ平面に吹き飛ばす力をかける
                float power = 10.0f;
                vec.x *= power;
                vec.z *= power;
                //Y座標にも力をかける
                vec.y = 5.0f;
                //吹き飛ばす
                player.AddImpulse(vec);
            }
        }        
    }
}

void EnemySlime::TransitionWanderState()
{
    state = State::Wander;
    //目標地点を設定
    SetRandomTargetPosition();
    //歩きアニメーション再生
    model->PlayAnimation(Anim_WalkFWD, true);
}

void EnemySlime::UpdateWanderState(float elapsedTime)
{
    //目標地点までXZ平面での距離判定
    float vx = targetPosition.x - position.x;
    float vz = targetPosition.z - position.z;
    float distSq = sqrtf(vx * vx + vz * vz);
    //目的地まで来たら待機ステートに移行
    if (distSq < radius * radius)
    {
        TransitionIdleState();
    }
    //目標地点へ移動
    MoveToTarget(elapsedTime, 0.5f);
    //プレイヤー索敵
    if (SearchPlayer())
    {
        TransitionPursuitState();
    }
}

void EnemySlime::TransitionIdleState()
{
    state = State::Idle;
    //タイマーをランダム設定
    stateTimer = Mathf::RandomRange(3.0f, 5.0f);
    //待機アニメーション再生
    model->PlayAnimation(Anim_IdleNoraml, true);
}

void EnemySlime::UpdateIdleState(float elapsedTime)
{
    //タイマー処理
    stateTimer -= elapsedTime;
    if (stateTimer < 0.0f)
    {
        TransitionWanderState();
    }
    //プレイヤー索敵
    if (SearchPlayer())
    {
        TransitionPursuitState();
    }
}

void EnemySlime::TransitionPursuitState()
{
    state = State::Pursuit;
    stateTimer = Mathf::RandomRange(3.0f, 5.0f);
    //歩きアニメーション再生
    model->PlayAnimation(Anim_WalkFWD, true);
}

void EnemySlime::UpdatePursuitState(float elapsedTime)
{
    //目標地点をプレイヤーの位置に変更
    targetPosition = Player::Instance().GetPosition();

    //目標地点へ移動
    MoveToTarget(elapsedTime, 1.0f);

    //タイマー処理
    stateTimer -= elapsedTime;
    if (stateTimer < 0.0f)
    {
        //待機ステートへ遷移
        TransitionIdleState();
    }
    float vx = targetPosition.x - position.x;
    float vy = targetPosition.y - position.y;
    float vz = targetPosition.z - position.z;
    //攻撃範囲内に入る
    float dist = sqrtf(vx * vx + vy * vy + vz * vz);
    if (dist < attackRange)
    {
        //攻撃ステートへ移行
        TransitionAttackState();
    }
}

void EnemySlime::TransitionAttackState()
{
    state = State::Attack;
    model->PlayAnimation(Anim_Attack1, false);
}

void EnemySlime::UpdateAttackState(float elapsedTime)
{
    float animationTime = model->GetCurrentAnimationSeconds();
    if (animationTime >= 0.1f && animationTime <= 0.35f)
    {
        //目玉ノードとプレイヤーの衝突処理
        CollisionNodeVsPlayer("EyeBall", 0.2f);
    }
    //攻撃アニメーションが終わったら戦闘待機ステートへ遷移
    if (!model->IsPlayAnimation())
    {
        TransitionIdleBattleState();
    }
}

void EnemySlime::TransitionIdleBattleState()
{
    state = State::IdleBattle;
    //数秒間待機するタイマーをランダム設定
    stateTimer = Mathf::RandomRange(2.0f, 3.0f);
    //戦闘待機アニメーション再生
    model->PlayAnimation(Anim_IdleBattele,true);
}

void EnemySlime::UpdateIdleBattleState(float elapsedTime)
{
    //目標地点をプレイヤー位置に設定
    targetPosition = Player::Instance().GetPosition();

    //タイマー処理
    stateTimer -= elapsedTime;
    if (stateTimer < 0.0f)
    {
        float vx = targetPosition.x - position.x;
        float vy = targetPosition.y - position.y;
        float vz = targetPosition.z - position.z;
        //攻撃範囲内に入る
        float dist = sqrtf(vx * vx + vy * vy + vz * vz);
        if (dist < attackRange)
        {
            //攻撃ステートへ移行
            TransitionAttackState();
        }
        else
        {
            //徘徊ステートへ遷移
            TransitionIdleState();
        }
        MoveToTarget(elapsedTime, 0.0f);
    }
}

void EnemySlime::TransitionDamageState()
{
    state = State::Damage;
    model->PlayAnimation(Anim_GetHit, false);
}

void EnemySlime::UpdateDamageState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        TransitionIdleBattleState();
    }
}

void EnemySlime::TransitionDeathState()
{
    state = State::Death;
    model->PlayAnimation(Anim_Die, false);
}

void EnemySlime::UpdateDeathState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        Destroy();
    }
}
