#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "ProjectileManager.h"
#include "Effect.h"

class Player : public Character
{
public:
    Player();
    ~Player() override;
    //インスタンス
    static Player& Instance();

    //更新処理
    void Update(float olapsedTime);

    //描画処理
    void Render(ID3D11DeviceContext* dc, Shader* shader);

    //デバッグプリミティブ描画
    void DrawDebugPrimitive();

    //デバッグ用GUI
    void DrawDebugGUI();
private:
    //スティック入力値から移動ベクトルを取得
    DirectX::XMFLOAT3 GetMoveVec() const;

    //プレイヤーとエネミーとの衝突処理
    void CollisionPlayerVsEnemies();
    //プレイヤーとエネミーの衝突処理
    void CollisionProjectilesVsEnemies();
    //ノードとエネミーの衝突処理
    void CollisionNodeVsEnemies(const char* nodeName, float nodeRadius);

private:

    //弾丸入力処理
    void InputProjectile();
    //待機ステートへ遷移
    void TransitionIdleState();
    //待機ステート更新処理
    void UpdateIdleState(float elapsedTime);

    //移動入力処理
    bool InputMove(float elapsedTime);
    //移動ステートへ遷移
    void TransitionMoveState();
    //移動ステート更新処理
    void UpdateMoveState(float elapsedTime);

    //ジャンプ入力処理
    bool InputJump();
    //ジャンプステートへ遷移
    void TransitionJumpState();
    //ジャンプステート更新処理
    void UpdateJumpState(float elapsedTime);
    //着地ステートへ遷移
    void TransitionLandState();
    //着地ステート更新処理
    void UpdateLandState(float elapsedTime);

    //攻撃入力処理
    bool InputAttack();
    //攻撃ステートへ遷移
    void TransitionAttackState();
    //攻撃ステート更新
    void UpdateAttackState(float elapsedTime);

    //ダメージステート遷移
    void TransitionDamageState();
    //ダメージステート更新
    void UpdateDamageState(float elapsedTime);

    //死亡ステート遷移
    void TransitionDeathState();
    //死亡ステート更新
    void UpdateDeathState(float elapsedTime);

    //復活ステート遷移
    void TransitionReviveState();
    //復活ステート更新
    void UpdateReviveState(float elapsedTime);

    //ステート
    enum class State
    {
        Idle,
        Move,
        Jump,
        Land,
        Attack,
        Damage,
        Death,
        Revive
    };

protected:
    void OnLanding() override;
    void OnDamaged()override;
    void OnDead()override;
private:
    Model* model = nullptr;
    float       moveSpeed = 7.0f;
    float       turnSpeed = DirectX::XMConvertToRadians(720);
    float       jumpSpeed = 20.0f;
    /*float       gravity = -1.0f;
    DirectX::XMFLOAT3 velocity = { 0,0,0 };*/

    int         jumpCount = 0;
    int         jumpLimit = 2;

    State state = State::Idle;

    ProjectileManager projectileManager;

    Effect*     hitEffect = nullptr;
    Effect*     auraEffect = nullptr;
    
    //アニメーション
    enum Animation
    {
        Anim_Attack,
        Anim_Death,
        Anim_Falling,
        Anim_GetHit1,
        Anim_GetHit2,
        Anim_Idle,
        Anim_Jump,
        Anim_Jump_Flip,
        Anim_Landing,
        Anim_Revive,
        Anim_Running,
        Anim_Walking,
    };

    float leftHandRadius = 0.4f;
    bool attackCollisionFlag;
};