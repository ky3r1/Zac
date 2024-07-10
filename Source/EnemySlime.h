#pragma once

#include "Graphics/Model.h"
#include "Enemy.h"

//スライム
class EnemySlime : public Enemy
{
public:
    EnemySlime();
    ~EnemySlime() override;

    //更新処理
    void Update(float elapsedTime);

    //描画処理
    void Render(ID3D11DeviceContext* dc, Shader* shader) override;

    //デバッグプリミティブ描画
    void DrewDebugPrimitive()override;

    //縄張り設定
    void SetTerritory(const DirectX::XMFLOAT3& origin, float range);
private:
    //プレイヤー索敵
    bool SearchPlayer();

    //ターゲット位置をランダム設定
    void SetRandomTargetPosition();

    //目標地点への移動
    void MoveToTarget(float elapsedTime, float speedRate);

    //ノードとプレイヤーの衝突処理
    void CollisionNodeVsPlayer(const char* nodeName, float boneRadius);
protected:
    //死亡したときに呼ばれる
    void OnDead() override;

    //ダメージを受けたときに呼ばれる
    void OnDamaged() override;
private:
    //徘徊ステート遷移
    void TransitionWanderState();
    //徘徊ステート更新
    void UpdateWanderState(float elapsedTime);

    //待機ステート遷移
    void TransitionIdleState();
    //待機ステート更新
    void UpdateIdleState(float elapsedTime);

    //待機ステート遷移
    void TransitionPursuitState();
    //待機ステート更新
    void UpdatePursuitState(float elapsedTime);

    //攻撃ステート遷移
    void TransitionAttackState();
    //攻撃ステート更新
    void UpdateAttackState(float elapsedTime);

    //攻撃待機ステート遷移
    void TransitionIdleBattleState();
    //攻撃待機ステート更新
    void UpdateIdleBattleState(float elapsedTime);

    //ダメージステート遷移
    void TransitionDamageState();
    //ダメージステート更新
    void UpdateDamageState(float elapsedTime);

    //死亡ステート遷移
    void TransitionDeathState();
    //死亡ステート更新
    void UpdateDeathState(float elapsedTime);
private:
    //ステート
    enum class State
    {
        Wander,
        Idle,
        Pursuit,
        Attack,
        IdleBattle,
        Damage,
        Death
    };

    enum Animation
    {
        Anim_IdleNoraml,
        Anim_IdleBattele,
        Anim_Attack1,
        Anim_Attack2,
        Anim_WalkFWD,
        Anim_WalkBWD,
        Anim_WalkLeft,
        Anim_WalkRight,
        Anim_RunFWD,
        Anim_SenseSomthingST,
        Anim_SenseSomthingPRT,
        Anim_Taunt,
        Anim_Victory,
        Anim_GetHit,
        Anim_Dizzy,
        Anim_Die,
    };

private:
    Model* model = nullptr;
    State state = State::Wander;
    DirectX::XMFLOAT3 targetPosition = { 0,0,0 };
    DirectX::XMFLOAT3 territoryOrigin = { 0.0f,0.0f,0.0f };
    float territoryRange = 10.0f;
    float moveSpeed = 3.0f;
    float turnSpeed = DirectX::XMConvertToRadians(360);
    float stateTimer = 0.0f;
    float searchRange = 5.0f;
    float attackRange = 1.5f;
};